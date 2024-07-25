import logging
import time
import os
import cv2
import numpy as np
import tensorflow as tf
import threading
from tf_pose.estimator import TfPoseEstimator
from tf_pose.networks import get_graph_path, model_wh

logger = logging.getLogger('TfPoseEstimator-Video-WebCam')
logger.setLevel(logging.DEBUG)
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)
formatter = logging.Formatter('[%(asctime)s] [%(name)s] [%(levelname)s] [%(threadName)s] %(message)s')
ch.setFormatter(formatter)
logger.addHandler(ch)

fps_time = 0
last_logged_time_video = time.time()
last_logged_time_webcam = time.time()

# 비디오 파일 경로 및 설정 값들 직접 지정
video_path = 'videos/test3.mp4'
resolution = '432x368'
model = 'mobilenet_thin'
show_process = False
showBG = True
use_tensorrt = False  # TensorRT 사용 여부
frame_skip = 5  # 프레임 건너뛰기 간격

def str2bool(v):
    return v.lower() in ("yes", "true", "t", "1")

def initialize_pose_estimator(model, resolution):
    logger.debug('initialization %s : %s' % (model, get_graph_path(model)))
    model_path = get_graph_path(model)
    if not os.path.isfile(model_path):
        raise Exception(f"Model file does not exist: {model_path}")

    w, h = model_wh(resolution)
    if w == 0 or h == 0:
        raise Exception(f"Invalid resolution: {resolution}")

    e = TfPoseEstimator(model_path, target_size=(w, h), trt_bool=use_tensorrt)
    return e, w, h

def log_human_positions(humans, source):
    for human in humans:
        for i in range(len(human.body_parts)):
            body_part = human.body_parts[i]
            rounded_x = round(body_part.x, 2)
            rounded_y = round(body_part.y, 2)
            logger.info(f'{source} - Body part {i}: ({rounded_x}, {rounded_y})')

def process_video():
    global fps_time, last_logged_time_video
    pose_estimator_video, w, h = initialize_pose_estimator(model, resolution)

    try:
        # 비디오 캡처 초기화
        if not os.path.isfile(video_path):
            raise Exception(f"Video file does not exist: {video_path}")
        video_cap = cv2.VideoCapture(video_path)
        if not video_cap.isOpened():
            raise Exception(f"Error opening video stream or file: {video_path}")

        frame_count = 0

        while video_cap.isOpened():
            ret_val_video, video_frame = video_cap.read()
            if not ret_val_video or video_frame is None or video_frame.size == 0:
                logger.debug('No frame retrieved from video')
                break

            frame_count += 1
            if frame_count % frame_skip != 0:
                continue

            try:
                video_frame = cv2.resize(video_frame, (w, h))
                humans_video = pose_estimator_video.inference(video_frame, resize_to_default=(w > 0 and h > 0), upsample_size=4.0)
                if not showBG:
                    video_frame = np.zeros(video_frame.shape)
                video_frame = TfPoseEstimator.draw_humans(video_frame, humans_video, imgcopy=False)

                cv2.putText(video_frame, "FPS: %f" % (1.0 / (time.time() - fps_time)), (10, 10),  cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                cv2.imshow('Video Pose Estimation', video_frame)

                current_time = time.time()
                if current_time - last_logged_time_video >= 1:
                    log_human_positions(humans_video, 'Video')
                    last_logged_time_video = current_time
            except Exception as e:
                logger.error(f"Error during video pose estimation: {e}")

            fps_time = time.time()
            if cv2.waitKey(1) == 27:
                break

        video_cap.release()
        cv2.destroyAllWindows()
    except Exception as e:
        logger.error(f"An error occurred in video processing: {e}")

def process_webcam():
    global fps_time, last_logged_time_webcam
    pose_estimator_webcam, w, h = initialize_pose_estimator(model, resolution)

    try:
        # 웹캠 캡처 초기화
        webcam_cap = cv2.VideoCapture(0)
        if not webcam_cap.isOpened():
            raise Exception(f"Error opening webcam stream")

        frame_count = 0

        while webcam_cap.isOpened():
            ret_val_webcam, webcam_frame = webcam_cap.read()
            if not ret_val_webcam or webcam_frame is None or webcam_frame.size == 0:
                logger.debug('No frame retrieved from webcam')
                break

            frame_count += 1
            if frame_count % frame_skip != 0:
                continue

            try:
                webcam_frame = cv2.resize(webcam_frame, (w, h))
                humans_webcam = pose_estimator_webcam.inference(webcam_frame, resize_to_default=(w > 0 and h > 0), upsample_size=4.0)
                if not showBG:
                    webcam_frame = np.zeros(webcam_frame.shape)
                webcam_frame = TfPoseEstimator.draw_humans(webcam_frame, humans_webcam, imgcopy=False)

                cv2.putText(webcam_frame, "FPS: %f" % (1.0 / (time.time() - fps_time)), (10, 10),  cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                cv2.imshow('WebCam Pose Estimation', webcam_frame)

                current_time = time.time()
                if current_time - last_logged_time_webcam >= 1:
                    log_human_positions(humans_webcam, 'WebCam')
                    last_logged_time_webcam = current_time
            except Exception as e:
                logger.error(f"Error during webcam pose estimation: {e}")

            fps_time = time.time()
            if cv2.waitKey(1) == 27:
                break

        webcam_cap.release()
        cv2.destroyAllWindows()
    except Exception as e:
        logger.error(f"An error occurred in webcam processing: {e}")

if __name__ == '__main__':
    # GPU 설정
    physical_devices = tf.config.experimental.list_physical_devices('GPU')
    if physical_devices:
        try:
            tf.config.experimental.set_memory_growth(physical_devices[0], True)
            tf.config.experimental.set_virtual_device_configuration(
                physical_devices[0],
                [tf.config.experimental.VirtualDeviceConfiguration(memory_limit=4096)]
            )
            logger.debug('GPU is set')
        except RuntimeError as e:
            logger.error(f"Error during GPU setup: {e}")

    try:
        # 멀티스레딩으로 비디오와 웹캠 프레임 처리
        video_thread = threading.Thread(target=process_video, name="VideoThread")
        webcam_thread = threading.Thread(target=process_webcam, name="WebCamThread")

        video_thread.start()
        webcam_thread.start()

        video_thread.join()
        webcam_thread.join()
    except Exception as e:
        logger.error(f"An error occurred: {e}")
logger.debug('finished+')
