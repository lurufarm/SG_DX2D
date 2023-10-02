// LuruEngine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "framework.h"
#include "sgRenderer.h"

// TODO: 라이브러리 함수의 예제입니다.
void fnLuruEngine()
{
}


namespace sg
{
	using namespace math;

	float sgLerp(float a, float b, float t)
	{
		return (1 - t) * a + t * b;
	};

	float sgGetAngle(Vector2 dir)
	{
		float angleRad = std::acos(dir.x); // acos 함수를 사용하여 x축과의 각도를 구한다.
		if (dir.y < 0) // 방향 벡터의 y값이 음수면 각도를 음수로 변환한다.
		{
			angleRad = -angleRad;
		}
		return angleRad * 180.0f / 3.141592f;
	}

	float sgGetAngleInRadian(float degree)
	{
		return degree * (3.141592f / 180.0f);
	}

	Vector2 sgGetBeamPos(float radius, float angle, Vector2 startPos)
	{
		float x = radius * cos(angle) + startPos.x;
		float y = radius * sin(angle) + startPos.y;

		return Vector2(x, y);
	}
}
