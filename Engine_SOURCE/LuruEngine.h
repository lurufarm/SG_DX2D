#pragma once

#include <string>
#include <Windows.h>
#include <assert.h>

#include <vector>		// 배열
#include <list>			// 링크드리스트
#include <map>			// 이진트리
#include <bitset>		// 비트 배열을 편하게 사용할 수 있게 해주는 라이브러리
#include <set>			// 해시 테이블
#include <functional>	// 함수 포인터

#include <cmath>		// 수학
#include <algorithm>	// 정렬 알고리즘 등등
#include <limits>		// 부동 소수점 표현 및 반올림과 관련된 클래스 탬플릿 numeric_limits 및 두개의 열거형을 정의합니다.
#include <memory>		// 메모리 관련 라이브러리
#include <filesystem>	// 파일 입출력 편하게 도와주는 라이브러리

#include "CommonInclude.h"
#include "sgEnums.h"
#include "sgMath.h"



namespace sg
{
	using namespace math;

	float sgLerp(float a, float b, float t);
	float sgGetAngle(Vector2 dir);
	float sgGetAngleInRadian(float degree);
	Vector2 sgGetBeamPos(float radius, float angle, Vector2 startPos);
}