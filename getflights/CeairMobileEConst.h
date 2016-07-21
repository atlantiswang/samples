
#pragma once

const unsigned char MS_[] =
{
	0X76, 0X5D, 0XD5, 0XC3, 0XD9, 0XDF, 0X44, 0X21, 0XAE, 0XD1, 0XFE, 0XAA, 0XDA, 0XBC, 0X69, 0X12, 0XF0, 0X6B, 0X96, 0XE1, 0X37, 0XD2, 0XDD, 0X2C, 0X0E, 0X7D, 0XE0, 0X92, 0XE6, 0X6A, 0X6C, 0X54
	,0X5B, 0XCA, 0XB3, 0XC4, 0X9A, 0X1D, 0X1B, 0X01, 0X5E, 0XF7, 0X48, 0X71, 0XA1, 0X2C, 0XCF, 0X24 
	,0X1D, 0XDB, 0XA9, 0X1C, 0X9B, 0X3D, 0XC8, 0X25, 0X84, 0X2F, 0X64, 0XD0, 0X33, 0X02, 0XAE, 0XD2, 0XEE, 0XAA, 0X84, 0XC2
};
//AES_Key 是MS_的前0：31字节，共32字节
const unsigned char AES_Key[] = 
{
	0X76, 0X5D, 0XD5, 0XC3, 0XD9, 0XDF, 0X44, 0X21, 0XAE, 0XD1, 0XFE, 0XAA, 0XDA, 0XBC, 0X69, 0X12, 0XF0, 0X6B, 0X96, 0XE1, 0X37, 0XD2, 0XDD, 0X2C, 0X0E, 0X7D, 0XE0, 0X92, 0XE6, 0X6A, 0X6C, 0X54, 0
};
//AES_IV是MS_的前32：47节，共16字节
const unsigned char AES_IV[] = {0X5B, 0XCA, 0XB3, 0XC4, 0X9A, 0X1D, 0X1B, 0X01, 0X5E, 0XF7, 0X48, 0X71, 0XA1, 0X2C, 0XCF, 0X24, 0};

const unsigned char RNC_[] =
{
	0X00, 0X15, 0X00, 0X1E, 0X69, 0XCA, 0XCB, 0X03, 0X66, 0X56, 0XB9, 0XAD, 0X10, 0X1D, 0X80, 0X4D, 0X97, 0XF7, 0X22, 0X12, 0X75, 0X25, 0X89, 0X54, 0XB7, 0XBD, 0X07, 0X4C, 0XAF, 0X0E, 0X71, 0XB9
};

const unsigned char RNS_[] =
{
	0X54, 0X9E, 0XAE, 0X7D, 0X9B, 0X82, 0X64, 0XA3, 0X7E, 0XC4, 0X8B, 0X85, 0XDD, 0X06, 0X83, 0XCA, 0XBE, 0XD8, 0X72, 0XBF, 0X0E, 0XC8, 0XCC, 0XB5, 0X3E, 0X4C, 0X86, 0X08, 0X1E, 0X0D, 0X1B, 0X33
};

const unsigned char MasterConst[] = 
{
	0X6D, 0X61, 0X73, 0X74, 0X65, 0X72, 0X20, 0X73, 0X65, 0X63, 0X72, 0X65, 0X74, 0X32
};

#define CEAIR_ME_TYPE1_CONTENT_LEN	(0X45)
#define CEAIR_ME_TYPE2_CONTENT_LEN	(0X368)
#define CEAIR_ME_SEVER_KEY_LEN	(0X70)

const BYTE ServerConst[] = 
{
	0X6B, 0X65, 0X79, 0X20, 0X65, 0X78, 0X70, 0X61, 0X6E, 0X73, 0X69, 0X6F, 0X6E
};

typedef struct _tagCeairMERecvRawHeader
{
	unsigned char	u8Type1;
	unsigned char	uType1ContentBytes[4];
	unsigned char	u8Type1Content[CEAIR_ME_TYPE1_CONTENT_LEN];
	unsigned char	u8Type2;
	unsigned char	uType2ContentBytes[4];
	unsigned char	u8Type2Content[CEAIR_ME_TYPE2_CONTENT_LEN];
	unsigned char	u8Type3;
	unsigned char	uType3ContentBytes[4];
	unsigned char	u8Type3Content[CEAIR_ME_SEVER_KEY_LEN];//Server key数据
}SCeairMERecvRawHeader;

typedef struct _tagCeairFlightInfo
{
	CStringA	straCompany;
	CStringA	straFromCityCode;
	CStringA	straToCityCode;
	CStringA	straFlightNo;
	CStringA	straFromDate;
	int			nPrice;
	int			nRemainSeat;
	_tagCeairFlightInfo()
	{
		straCompany = "";
		straFromCityCode = "";
		straToCityCode = "";
		straFlightNo = "";
		straFromDate = "";
		nPrice = 0;
		nRemainSeat = 0;
	}

	_tagCeairFlightInfo & operator=(const _tagCeairFlightInfo & info)
	{
		straCompany = info.straCompany;
		straFromCityCode = info.straFromCityCode;
		straToCityCode = info.straToCityCode;
		straFlightNo = info.straFlightNo;
		straFromDate = info.straFromDate;
		nPrice = info.nPrice;
		nRemainSeat = info.nRemainSeat;

		return *this;
	}
}SCeairFlightInfo;