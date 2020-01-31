# 사용자 분석

import seaborn as sns
import pandas as pd
import operator as op
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.font_manager as fm

print('버전: ', mpl.__version__)
print('설치 위치: ', mpl.__file__)
print('설정 위치: ', mpl.get_configdir())
print('캐시 위치: ', mpl.get_cachedir())

path = 'C:/Users/kuro1/AppData/Local/Microsoft/Windows/Fonts/D2Coding-Ver1.3.2-20180524-all.ttc'
font_name = fm.FontProperties(fname=path, size=50).get_name()
print(font_name)
plt.rc('font', family=font_name)

kind = {0: "총류",
        1: "철학",
        2: "종교",
        3: "사회",
        4: "자연",
        5: "기술",
        6: "예술",
        7: "언어",
        8: "문학",
        9: "역사"}

kind_rev = {v: k for k, v in kind.items()}

book_li = [0, 0, 0, 2, 3, 1, 1, 7, 7, 7, 4, 4, 4, 4, 4]

person = [0 for i in range(10)]  # 종류별 책의 수 세기
for book in book_li:
    person[book] += 1

reg_di = {p: round(i / sum(person), 2) for p, i in enumerate(person)}  # 정규화
reg_li_s = sorted(reg_di.items(), key=op.itemgetter(1), reverse=True)  # value로 정렬
print("사용자의 분야별 서적 비율: " + str(reg_di))
print("사용자의 분야별 서적 비율 정렬: " + str(reg_li_s))
print("가장 많이본 분류: " + str(kind[reg_li_s[0][0]]) + ", 비율: " + str(reg_li_s[0][1]))
print("두 번째로 많이본 분류: " + str(kind[reg_li_s[1][0]]) + ", 비율: " + str(reg_li_s[1][1]))
print("독서 분류 편향도 (분산): " + str(np.var([val for key, val in reg_li_s])))  # 높을 수록 편향적인 독서를 한다 -> 편향을 줄이기 위한 추천이 필요
print()

# plt.bar(list(reg_di.keys()), list(reg_di.values()), width=0.9, color="green")
plt.bar([kind[i] for i in reg_di.keys()], list(reg_di.values()), width=0.9, color="green")
plt.xlabel('분류')
plt.ylabel('책')
plt.show()

book_li = [1, 2, 3, 4, 4, 5, 6, 7]

person = [0 for i in range(len(book_li))]  # 종류별 책의 수 세기
for book in book_li:
    person[book] += 1

reg_di = {p: round(i / sum(person), 2) for p, i in enumerate(person)}  # 정규화
reg_li_s = sorted(reg_di.items(), key=op.itemgetter(1), reverse=True)  # value로 정렬
print("사용자의 분야별 서적 비율: " + str(reg_di))
print("사용자의 분야별 서적 비율 정렬: " + str(reg_li_s))
print("가장 많이본 분류: " + str(kind[reg_li_s[0][0]]) + ", 비율: " + str(reg_li_s[0][1]))
print("두 번째로 많이본 분류: " + str(kind[reg_li_s[1][0]]) + ", 비율: " + str(reg_li_s[1][1]))
print("독서 분류 편향도 (분산): " + str(np.var([val for key, val in reg_li_s])))
print()

book_li = [1, 1, 1, 1, 1, 1, 1, 1]

person = [0 for i in range(len(book_li))]  # 종류별 책의 수 세기
for book in book_li:
    person[book] += 1

reg_di = {p: round(i / sum(person), 2) for p, i in enumerate(person)}  # 정규화
reg_li_s = sorted(reg_di.items(), key=op.itemgetter(1), reverse=True)  # value로 정렬
print("사용자의 분야별 서적 비율: " + str(reg_di))
print("사용자의 분야별 서적 비율 정렬: " + str(reg_li_s))
print("가장 많이본 분류: " + str(kind[reg_li_s[0][0]]) + ", 비율: " + str(reg_li_s[0][1]))
print("두 번째로 많이본 분류: " + str(kind[reg_li_s[1][0]]) + ", 비율: " + str(reg_li_s[1][1]))
print("독서 분류 편향도 (분산): " + str(np.var([val for key, val in reg_li_s])))
print()
