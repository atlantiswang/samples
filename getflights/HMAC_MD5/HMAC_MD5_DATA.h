#pragma once

typedef struct
{
	DWORD	p[4];
	DWORD	q[4][16];
} TYPE_MD5DATA;

/* ------------------------------------------------
		 MD5关键参数，修改即可形成不同的变体
   ------------------------------------------------ */
const TYPE_MD5DATA MD5_ARGUMENTS = {
	// 初始状态
	{0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476},

	// 变换操作偏移量表
	{0xD76AA478,0xE8C7B756,0x242070DB,0xC1BDCEEE,
	 0xF57C0FAF,0x4787C62A,0xA8304613,0xFD469501,
	 0x698098D8,0x8B44F7AF,0xFFFF5BB1,0x895CD7BE,
	 0x6B901122,0xFD987193,0xA679438E,0x49B40821,

	 0xF61E2562,0xC040B340,0x265E5A51,0xE9B6C7AA,
	 0xD62F105D,0x02441453,0xD8A1E681,0xE7D3FBC8,
	 0x21E1CDE6,0xC33707D6,0xF4D50D87,0x455A14ED,
	 0xA9E3E905,0xFCEFA3F8,0x676F02D9,0x8D2A4C8A,

	 0xFFFA3942,0x8771F681,0x6D9D6122,0xFDE5380C,
	 0xA4BEEA44,0x4BDECFA9,0xF6BB4B60,0xBEBFBC70,
	 0x289B7EC6,0xEAA127FA,0xD4EF3085,0x04881D05,
	 0xD9D4D039,0xE6DB99E5,0x1FA27CF8,0xC4AC5665,

	 0xF4292244,0x432AFF97,0xAB9423A7,0xFC93A039,
	 0x655B59C3,0x8F0CCC92,0xFFEFF47D,0x85845DD1,
	 0x6FA87E4F,0xFE2CE6E0,0xA3014314,0x4E0811A1,
	 0xF7537E82,0xBD3AF235,0x2AD7D2BB,0xEB86D391}
};

// 变换操作移位表
const BYTE MDShiftTable[][4] = {{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}};

// 填充数据
const BYTE MDPadding[] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// MD5基本位操作函数
#define F(x, y, z)	(((x) & (y)) | ((~x) & (z)))
#define G(x, y, z)	(((x) & (z)) | ((y) & (~z)))
#define H(x, y, z)	((x) ^ (y) ^ (z))
#define I(x, y, z)	((y) ^ ((x) | (~z)))

// 位循环左移位操作
#define ROL(x, n)	(((x) << (n)) | ((x) >> (32-(n))))

// ---------变换操作----------
// 第一轮变换基本操作
#define FF(a, b, c, d, x, s, t)	{ \
	(a) += F((b), (c), (d)) + (x) + (t); \
	(a) = ROL((a), (s)); \
	(a) += (b); \
}

// 第二轮变换基本操作
#define GG(a, b, c, d, x, s, t)	{ \
	(a) += G((b), (c), (d)) + (x) + (t); \
	(a) = ROL((a), (s)); \
	(a) += (b); \
}

// 第三轮变换基本操作
#define HH(a, b, c, d, x, s, t)	{ \
	(a) += H((b), (c), (d)) + (x) + (t); \
	(a) = ROL((a), (s)); \
	(a) += (b); \
}

// 第四轮变换基本操作
#define II(a, b, c, d, x, s, t)	{ \
	(a) += I((b), (c), (d)) + (x) + (t); \
	(a) = ROL((a), (s)); \
	(a) += (b); \
}
