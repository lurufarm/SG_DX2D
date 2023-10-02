#pragma once

#include <string>
#include <Windows.h>
#include <assert.h>

#include <vector>		// �迭
#include <list>			// ��ũ�帮��Ʈ
#include <map>			// ����Ʈ��
#include <bitset>		// ��Ʈ �迭�� ���ϰ� ����� �� �ְ� ���ִ� ���̺귯��
#include <set>			// �ؽ� ���̺�
#include <functional>	// �Լ� ������

#include <cmath>		// ����
#include <algorithm>	// ���� �˰��� ���
#include <limits>		// �ε� �Ҽ��� ǥ�� �� �ݿø��� ���õ� Ŭ���� ���ø� numeric_limits �� �ΰ��� �������� �����մϴ�.
#include <memory>		// �޸� ���� ���̺귯��
#include <filesystem>	// ���� ����� ���ϰ� �����ִ� ���̺귯��

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