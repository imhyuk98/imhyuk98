def calculate_bmi(weight, height):
    # Calculate BMI by dividing weight (kg) by height (m) squared
    bmi = weight / (height ** 2)
    return bmi


def calculate_bmr(weight, height, age, gender):
    # Calculate basal metabolic rate based on gender
    if gender == "남성":
        bmr = 66 + (13.75 * weight) + (5 * (height * 100)) - (6.75 * age)
    else:
        bmr = 655 + (9.56 * weight) + (1.85 * (height * 100)) - (4.68 * age)
    return bmr


def suggest_diet(bmi, bmr):
    if bmi < 18.5:
        rice_amount = bmr * 0.3
    elif bmi < 24.9:
        rice_amount = bmr * 0.4
    elif bmi < 29.9:
        rice_amount = bmr * 0.5
    else:
        rice_amount = bmr * 0.6

    diet = {
        "구간": "",
        "식단": {
            "아침": {
                "메뉴": "볶음 계란",
                "음식 양": "계란 2개, 채소"
            },
            "점심": {
                "메뉴": "닭가슴살 샐러드",
                "음식 양": "닭가슴살 100g, 생채소"
            },
            "저녁": {
                "메뉴": "그릴 스테이크",
                "음식 양": "쇠고기 스테이크 150g, 채소"
            }
        },
        "밥의 그램 수": rice_amount
    }

    if bmi < 18.5:
        diet["구간"] = "저체중"
    elif bmi < 24.9:
        diet["구간"] = "정상 체중"
    elif bmi < 29.9:
        diet["구간"] = "과체중"
    else:
        diet["구간"] = "비만"

    return diet


while True:
    gender = input("성별을 입력하세요 (남성 또는 여성): ")

    if gender in ["남성", "여성"]:
        break
    else:
        print("유효한 성별을 입력하세요 (남성 또는 여성).")

height = float(input("키(cm)를 입력하세요: ")) / 100
weight = float(input("몸무게(kg)를 입력하세요: "))
age = int(input("나이를 입력하세요: "))

bmi = calculate_bmi(weight, height)
print("당신의 BMI는 {:.1f}입니다.".format(bmi))

bmr = calculate_bmr(weight, height, age, gender)
print("당신의 기초대사량은 {:.1f}입니다.".format(bmr))

diet_suggestion = suggest_diet(bmi, bmr)
print("당신은 {} 구간입니다.".format(diet_suggestion["구간"]))
print("다음은 {} 구간에 추천되는 식단입니다:".format(diet_suggestion["구간"]))
for meal, details in diet_suggestion["식단"].items():
    print("- {}: {}".format(meal, details["메뉴"]))
    print("  음식 양: {}".format(details["음식 양"]))
print("밥의 그램 수: {:.1f}g".format(diet_suggestion["밥의 그램 수"]))
