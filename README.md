# 분수(Fraction) ADT

정수형 분자와 분모를 가지는 분수 자료형에 대한 연산 정의

## 1. 데이터 타입
- `Fraction`: `int numerator` (분자), `int denominator` (분모)

## 2. 연산 (Operations)
- `create_fraction(int n, int d)`: 분자와 분모를 입력받아 분수 생성
- `simplify(Fraction f)`: 기약분수로 변환
- `add(Fraction a, Fraction b)`: 덧셈
- `subtract(Fraction a, Fraction b)`: 뺄셈
- `multiply(Fraction a, Fraction b)`: 곱셈
- `divide(Fraction a, Fraction b)`: 나눗셈
- `parse_fraction(char* str)`: 문자열(A/B)을 분수로 변환
- `print_fraction(Fraction f)`: 분수 출력 (기약분수, 정수 형태 구분)

## 3. 오류 핸들링
- 분모가 0이 되는 경우 처리 (0으로 나누기 오류 방지)
- 입력 형식 오류 처리
