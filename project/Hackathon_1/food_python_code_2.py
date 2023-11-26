import random

def recommend_protein_foods():
    protein_foods = {
        '닭가슴살': {'description': '단백질이 풍부하고 지방 함량이 낮아 근육 회복과 성장에 도움을 줍니다.', 'protein_per_100g': 23, 'calories_per_100g': 113},
        '연어': {'description': '오메가-3 지방산과 단백질이 풍부하여 근육 회복과 염증 감소에 도움을 줍니다.', 'protein_per_100g': 20, 'calories_per_100g': 206},
        '계란': {'description': '단백질과 아미노산이 다양하게 포함되어 근육 회복과 성장에 도움을 줍니다.', 'protein_per_100g': 13, 'calories_per_100g': 155},
        '콩': {'description': '식물성 단백질과 식이섬유가 풍부하여 근육 회복과 영양 공급에 도움을 줍니다.', 'protein_per_100g': 9, 'calories_per_100g': 130},
        '토마토': {'description': '비타민 C와 리코펜이 풍부하여 근육 손상 회복과 염증 감소에 도움을 줍니다.', 'protein_per_100g': 1, 'calories_per_100g': 18},
        # 추가 단백질 음식들
        '소고기': {'description': '고기의 대표적인 단백질 음식으로, 철분과 비타민 B12가 풍부합니다.', 'protein_per_100g': 26, 'calories_per_100g': 250},
        '흰살생선': {'description': '저지방이고 단백질이 풍부한 생선으로, 심혈관 건강에 도움을 줍니다.', 'protein_per_100g': 20, 'calories_per_100g': 96},
        '쇠고기': {'description': '단백질과 철분이 풍부한 고기로, 에너지 공급과 혈액 형성에 도움을 줍니다.', 'protein_per_100g': 36, 'calories_per_100g': 250},
        '북어': {'description': '고단백 저지방 식품으로, 다양한 영양소를 함유하고 있습니다.', 'protein_per_100g': 62, 'calories_per_100g': 315},
        '홍합': {'description': '고단백 저지방의 해산물로, 철분과 아연이 풍부합니다.', 'protein_per_100g': 18, 'calories_per_100g': 90},
        '아몬드': {'description': '식물성 단백질과 좋은 지방이 풍부한 견과류로, 에너지와 영양 공급에 도움을 줍니다.', 'protein_per_100g': 21, 'calories_per_100g': 579},
        '우유': {'description': '단백질, 칼슘, 비타민 등이 풍부한 유제품으로, 뼈 건강과 영양 공급에 도움을 줍니다.', 'protein_per_100g': 3, 'calories_per_100g': 61},
        '오징어': {'description': '저지방이고 단백질이 풍부한 해산물로, 철분과 다양한 영양소를 함유하고 있습니다.', 'protein_per_100g': 18, 'calories_per_100g': 85},
        '녹두': {'description': '식물성 단백질과 식이섬유가 풍부한 식품으로, 영양 공급과 소화에 도움을 줍니다.', 'protein_per_100g': 24, 'calories_per_100g': 336},
        '딸기': {'description': '비타민 C와 식이섬유가 풍부한 과일로, 항산화 효과와 소화에 도움을 줍니다.', 'protein_per_100g': 1, 'calories_per_100g': 32},
        '김치': {'description': '식이섬유와 유산균이 풍부한 음식으로, 소화와 장 건강에 도움을 줍니다.', 'protein_per_100g': 2, 'calories_per_100g': 15},
        '검은콩': {'description': '식물성 단백질과 식이섬유가 풍부한 식품으로, 영양 공급과 소화에 도움을 줍니다.', 'protein_per_100g': 20, 'calories_per_100g': 341},
        '단호박': {'description': '비타민 A와 식이섬유가 풍부한 식품으로, 항산화 효과와 소화에 도움을 줍니다.', 'protein_per_100g': 1, 'calories_per_100g': 34},
        '아보카도': {'description': '단백질과 좋은 지방이 풍부한 과일로, 에너지와 영양 공급에 도움을 줍니다.', 'protein_per_100g': 2, 'calories_per_100g': 160},
        '아욱': {'description': '식물성 단백질과 식이섬유가 풍부한 식품으로, 영양 공급과 소화에 도움을 줍니다.', 'protein_per_100g': 3, 'calories_per_100g': 28},
        '검정콩': {'description': '식물성 단백질과 식이섬유가 풍부한 식품으로, 영양 공급과 소화에 도움을 줍니다.', 'protein_per_100g': 21, 'calories_per_100g': 341},
        '멸치': {'description': '단백질과 다양한 영양소가 풍부한 해산물로, 에너지 공급과 영양 공급에 도움을 줍니다.', 'protein_per_100g': 64, 'calories_per_100g': 336},
        '올리브오일': {'description': '좋은 지방과 항산화 물질이 풍부한 기름으로, 영양 공급과 항염증 효과가 있습니다.', 'protein_per_100g': 0, 'calories_per_100g': 884},
        '고구마': {'description': '비타민 A와 식이섬유가 풍부한 식품으로, 항산화 효과와 소화에 도움을 줍니다.', 'protein_per_100g': 1, 'calories_per_100g': 86},
        '피스타치오': {'description': '식물성 단백질과 좋은 지방이 풍부한 견과류로, 에너지와 영양 공급에 도움을 줍니다.', 'protein_per_100g': 21, 'calories_per_100g': 562},
    }
    return protein_foods

def generate_random_menu(meal_count, protein_foods):
    menu = []
    for _ in range(meal_count):
        food = random.choice(list(protein_foods.keys()))
        menu.append(food)
    return menu

# 키 입력 받기
height = float(input('키(cm)를 입력하세요: '))

# 몸무게 입력 받기
weight = float(input('몸무게(kg)를 입력하세요: '))

# 연령 입력 받기
age = int(input('연령을 입력하세요: '))

# 성별 입력 받기
gender = validate_gender()

# 근골격량 입력 받기
muscle_mass = float(input('근골격량(kg)을 입력하세요: '))

# 활동 수준 입력 받기
activity_level = validate_activity_level()

# 일일 단백질 섭취량 계산
protein_intake = calculate_protein_intake(weight, muscle_mass, activity_level)

# 일일 칼로리 섭취량 계산
calorie_intake = calculate_calorie_intake(height, weight, age, gender, activity_level)

# 단백질 음식 추천
protein_foods = recommend_protein_foods()

print('\n일일 권장 섭취량:')
print('- 단백질: {}g'.format(protein_intake))
print('- 칼로리: {}kcal'.format(calorie_intake))

print('\n오늘의 추천 단백질 음식:')
menu = generate_random_menu(3, protein_foods)
for food in menu:
    print('- {}'.format(food))
    print('  설명:', protein_foods[food]['description'])
    print('  100g 당 단백질:', protein_foods[food]['protein_per_100g'], 'g')
    print('  100g 당 칼로리:', protein_foods[food]['calories_per_100g'], 'kcal')
