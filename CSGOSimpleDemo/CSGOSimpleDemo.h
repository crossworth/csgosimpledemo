#ifndef CSGO_SIMPLE_DEMO_H_
#define CSGO_SIMPLE_DEMO_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <algorithm>


#define PROFILER

#ifdef PROFILER

#include <chrono>

#define ProfileBlock() Profiler _me_profiler(__FUNCTION__, "")
#define ProfileBlockStr(x) Profiler _me_profiler(__FUNCTION__, x)
#define ProfileBlockStrMilliseconds(x) Profiler _me_profiler(__FUNCTION__, x, Profiler::Scale::MILLISECONDS)
#define ProfileBlockStrMicroseconds(x) Profiler _me_profiler(__FUNCTION__, x, Profiler::Scale::MICROSECONDS)

class Profiler {
public:

	enum class Scale {
		SECONDS,
		MILLISECONDS,
		MICROSECONDS
	};
	
	Profiler(const char *functionName, const char *text = "", Scale scale = Scale::MILLISECONDS) {
		std::string strFunctionName = std::string(functionName);
		std::string strText = std::string(text);
		mScale = scale;

		mFunctionName = strFunctionName;

		if (strText != "") {
			mFunctionName = mFunctionName + " " + strText;
		}


		mClock = std::chrono::high_resolution_clock::now();
	}

	~Profiler() {
		std::chrono::high_resolution_clock::time_point mClockTwo = std::chrono::high_resolution_clock::now();
		if (mScale == Scale::MICROSECONDS) {
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(mClockTwo - mClock).count();
			std::cout << mFunctionName << ": " << duration << " microseconds" << std::endl;
		} else if (mScale == Scale::MILLISECONDS) {
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(mClockTwo - mClock).count();
			std::cout << mFunctionName << ": " << duration << " milliseconds" << std::endl;
		} else {
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(mClockTwo - mClock).count();
			std::cout << mFunctionName << ": " << duration << " seconds" << std::endl;
		}
	}

private:
	Profiler();
	Scale mScale;
	std::chrono::high_resolution_clock::time_point mClock;
	std::string mFunctionName;
};

#endif



#ifdef _MSC_VER
#include <intrin.h>
#pragma warning( disable : 4996 ) // Disable _SCL_SECURE_NO_WARNINGS from Protobuf, if this don't work try disabling on the Project settings
#endif


// Valve proto's
#include "generated_proto/netmessages_public.pb.h"
#include "generated_proto/cstrike15_usermessages_public.pb.h"
#include "generated_proto/cstrike15_gcmessages.pb.h"
#include "generated_proto/steammessages.pb.h"


//
// Swap endian
//
#define SWAP16(n) (((n&0xFF00)>>8)|((n&0x00FF)<<8))
#define SWAP32(n) ((SWAP16((n&0xFFFF0000)>>16))|((SWAP16(n&0x0000FFFF))<<16))
#define SWAP64(n) ((SWAP32((n&0xFFFFFFFF00000000)>>32))|((SWAP32(n&0x00000000FFFFFFFF))<<32))


// 
// Demo
//
#define DEMO_HEADER_ID "HL2DEMO"
#define DEMO_PROTOCOL 4
#define MAX_OSPATH 260
#define NET_MAX_PAYLOAD (262144 - 4)

#define DEMO_RECORD_BUFFER_SIZE (2 * 1024 * 1024)
#define MAX_PLAYER_NAME_LENGTH 128
#define SIGNED_GUID_LEN 32
#define MAX_CUSTOM_FILES 4

#define ENTITY_SENTINEL 9999
#define NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS 10

// How many bits to use to encode an edict.
#define	MAX_EDICT_BITS 11 // # of bits needed to represent max edicts
// Max # of edicts in a level
#define	MAX_EDICTS (1 << MAX_EDICT_BITS)

#define FDEMO_NORMAL 0
#define FDEMO_USE_ORIGIN2 (1 << 0)
#define FDEMO_USE_ANGLES2 (1 << 1)
#define FDEMO_NOINTERP (1 << 2)	// don't interpolate between this an last view
#define MAX_SPLITSCREEN_CLIENTS	2

#define SPROP_UNSIGNED (1 << 0)	// Unsigned integer data.
#define SPROP_COORD (1 << 1)	// If this is set, the float/vector is treated like a world coordinate. Note that the bit count is ignored in this case.
#define SPROP_NOSCALE (1 << 2)	// For floating point, don't scale into range, just take value as is.
#define SPROP_ROUNDDOWN (1 << 3)	// For floating point, limit high value to range minus one bit unit
#define SPROP_ROUNDUP (1 << 4)	// For floating point, limit low value to range minus one bit unit
#define SPROP_NORMAL (1 << 5)	// If this is set, the vector is treated like a normal (only valid for vectors)
#define SPROP_EXCLUDE (1 << 6)	// This is an exclude prop (not excludED, but it points at another prop to be excluded).
#define SPROP_XYZE (1 << 7)	// Use XYZ/Exponent encoding for vectors.
#define SPROP_INSIDEARRAY (1 << 8)	// This tells us that the property is inside an array, so it shouldn't be put into the flattened property list. Its array will point at it when it needs to.
#define SPROP_PROXY_ALWAYS_YES (1 << 9)	// Set for datatable props using one of the default datatable proxies like SendProxy_DataTableToDataTable that always send the data to all clients.
#define SPROP_IS_A_VECTOR_ELEM (1 << 10)	// Set automatically if SPROP_VECTORELEM is used.
#define SPROP_COLLAPSIBLE (1 << 11)	// Set automatically if it's a datatable with an offset of 0 that doesn't change the pointer (ie: for all automatically-chained base classes).
#define SPROP_COORD_MP (1 << 12) // Like SPROP_COORD, but special handling for multiplayer games
#define SPROP_COORD_MP_LOWPRECISION (1 << 13) // Like SPROP_COORD, but special handling for multiplayer games where the fractional component only gets a 3 bits instead of 5
#define SPROP_COORD_MP_INTEGRAL (1 << 14) // SPROP_COORD_MP, but coordinates are rounded to integral boundaries
#define SPROP_CELL_COORD (1 << 15) // Like SPROP_COORD, but special encoding for cell coordinates that can't be negative, bit count indicate maximum value
#define SPROP_CELL_COORD_LOWPRECISION (1 << 16) // Like SPROP_CELL_COORD, but special handling where the fractional component only gets a 3 bits instead of 5
#define SPROP_CELL_COORD_INTEGRAL (1 << 17) // SPROP_CELL_COORD, but coordinates are rounded to integral boundaries
#define SPROP_CHANGES_OFTEN (1 << 18)	// this is an often changed field, moved to head of sendtable so it gets a small index
#define SPROP_VARINT (1 << 19)	// use var int encoded (google protobuf style), note you want to include SPROP_UNSIGNED if needed, its more efficient

#define DT_MAX_STRING_BITS 9
#define DT_MAX_STRING_BUFFERSIZE (1 << DT_MAX_STRING_BITS)	// Maximum length of a string that can be sent.

// OVERALL Coordinate Size Limits used in COMMON.C MSG_*BitCoord() Routines (and someday the HUD)
#define	COORD_INTEGER_BITS 14
#define COORD_FRACTIONAL_BITS 5
#define COORD_DENOMINATOR (1 << (COORD_FRACTIONAL_BITS))
#define COORD_RESOLUTION (1.0f / (COORD_DENOMINATOR))

// Special threshold for networking multiplayer origins
#define COORD_INTEGER_BITS_MP 11
#define COORD_FRACTIONAL_BITS_MP_LOWPRECISION 3
#define COORD_DENOMINATOR_LOWPRECISION (1 << (COORD_FRACTIONAL_BITS_MP_LOWPRECISION))
#define COORD_RESOLUTION_LOWPRECISION (1.0f / (COORD_DENOMINATOR_LOWPRECISION))

#define NORMAL_FRACTIONAL_BITS 11
#define NORMAL_DENOMINATOR ((1 << (NORMAL_FRACTIONAL_BITS)) - 1)
#define NORMAL_RESOLUTION (1.0f / (NORMAL_DENOMINATOR))

//
// Types
//
typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

//
// enum's
//
enum class DemoCommand {
	SIGNON = 1, // startup message
	PACKET, // network packet
	SYNCTICK, // client sync to demo tick
	CONSOLECMD, // console command
	USERCMD, // user command
	DATATABLES, // network data tables
	STOP, // end of ticks
	CUSTOMDATA, // blob binary data
	STRINGTABLES, // TODO(Pedro): what string tables bring?
	LASTCMD = STRINGTABLES // last command demofile
};

enum class UpdateType {
	EnterPVS = 0, // Entity came back into pvs, create new entity if one doesn't exist
	LeavePVS, // Entity left pvs
	DeltaEnt, // There is a delta for this entity.
	PreserveEnt, // Entity stays alive but no delta ( could be LOD, or just unchanged )
	Finished, // finished parsing entities successfully
	Failed, // parsing error occured while reading entities
};

// Spectator Movement modes
enum class ObserverMode {
	OBS_MODE_NONE = 0,	// not in spectator mode
	OBS_MODE_DEATHCAM,	// special mode for death cam animation
	OBS_MODE_FREEZECAM,	// zooms to a target, and freeze-frames on them
	OBS_MODE_FIXED,		// view from a fixed camera position
	OBS_MODE_IN_EYE,	// follow a player in first person view
	OBS_MODE_CHASE,		// follow a player in third person view
	OBS_MODE_POI,		// PASSTIME point of interest - game objective, big fight, anything interesting; added in the middle of the enum due to tons of hard-coded "<ROAMING" enum compares
	OBS_MODE_ROAMING,	// free roaming

	NUM_OBSERVER_MODES,
};

enum class EBitCoordType {
	kCW_None,
	kCW_LowPrecision,
	kCW_Integral
};

enum class CSGOTeamType {
	Spectator = 1,
	Terrorist,
	CounterTerrorist, // Check this again, this could be swaped
	Unknown
};

enum class SendPropType {
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY, // Only encodes the XY of a vector, ignores Z
	DPT_String,
	DPT_Array,	// An array of the base types (can't be of datatables).
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes
};

class DataBuffer : public std::basic_streambuf<char> {
public:

	explicit DataBuffer(const char *data, const size_t &length) {
		m_data = new char[length];
		std::memcpy(m_data, data, length);
		setg(m_data, m_data, m_data + length);
	}

	~DataBuffer() {
		delete[] m_data;
	}

	std::ios::pos_type seekoff(std::ios::off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which = std::ios_base::in) {
		if (dir == std::ios_base::end) {
			setg(eback(), egptr() - off, egptr());
		} else if (dir == std::ios_base::beg) {
			setg(eback(), eback() + off, egptr());
		} else {
			setg(eback(), gptr() + off, egptr());
		}

		return static_cast<std::ios::pos_type>(this->gptr() - this->eback());
	}

	std::ios::pos_type seekpos(std::ios::pos_type pos, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) {
		setg(eback(), eback() + static_cast<std::ios::off_type>(pos), egptr());
		return static_cast<std::ios::pos_type>(this->gptr() - this->eback());
	}

private:
	char *m_data;
};

class DataStream : public std::istream {
private:
	const int32 MaxVarInt64Bytes = 10;
	const int32 MaxVarInt32Bytes = 5;
public:
	DataStream(DataBuffer &buffer) : std::istream(&buffer) {}

	int8 readByte() {
		return get();
	}

	void readBytesToBuffer(void *buffer, const size_t size) {
		read(reinterpret_cast<char*>(buffer), size);
	}

	int16 readInt16() {
		int16 n;
		readBytesToBuffer(&n, sizeof(int16));
		return n;
	}

	int32 readInt32() {
		int32 n;
		readBytesToBuffer(&n, sizeof(int32));
		return n;
	}

	int64 readInt64() {
		int64 n;
		readBytesToBuffer(&n, sizeof(int64));
		return n;
	}

	float readFloat() {
		float n;
		readBytesToBuffer(&n, sizeof(n));
		return n;
	}

	int32 readVarInt32() {
		uint32 result = 0;
		int32 count = 0;
		uint32 b;

		do {
			if (count == DataStream::MaxVarInt32Bytes) {
				return result;
			}

			b = readByte();
			result |= (b & 0x7F) << (7 * count);
			++count;
		} while (b & 0x80);

		return result;
	}

	int64 readVarInt64() {
		uint64 result = 0;
		int32 count = 0;
		uint64 b;

		do {
			if (count == DataStream::MaxVarInt32Bytes) {
				return result;
			}

			b = readByte();
			result |= static_cast<uint64>(b & 0x7F) << (7 * count);
			count++;
		} while (b & 0x80);

		return result;
	}

	std::string readString(const unsigned int &limit, bool breakNewLine = false) {
		std::string output;
		uint32 currentPos = 0;

		while (1) {
			char val = readByte();
			if (val == 0) {
				break;
			} else if (breakNewLine && val == '\n') {
				break;
			}

			if (currentPos < (limit - 1)) {
				output.push_back(val);
				currentPos++;
			}
		}

		return output;
	}
};

class DataBitStream {
	const int32 MaxVarInt64Bytes = 10;
	const int32 MaxVarInt32Bytes = 5;
public:
	DataBitStream(const char *buffer, const uint32 &numBytes) : m_sizeBits(numBytes * 8), m_currentPosition(0) {
		m_buffer = new char[numBytes];
		std::memcpy(m_buffer, buffer, numBytes);
	}

	uint32 getCurrentPosition() const {
		return m_currentPosition;
	}

	uint32 getSizeBits() const {
		return m_sizeBits;
	}

	inline int32 ZigZagDecode32(uint32 n) {
		return(n >> 1) ^ -static_cast<int32>(n & 1);
	}

	inline int64 ZigZagDecode64(uint64 n) {
		return(n >> 1) ^ -static_cast<int64>(n & 1);
	}

	int32 readSignedVarInt32() { return ZigZagDecode32(readVarInt32()); }
	int64 readSignedVarInt64() { return ZigZagDecode64(readVarInt64()); }

	bool readBit() {
		bool result = false;

		if (m_currentPosition < m_sizeBits) {
			char currentByte = m_buffer[m_currentPosition / 8];
			result = (currentByte >> (m_currentPosition % 8)) & 1;
			m_currentPosition++;
		}

		return result;
	}

	uint32 readUBitLong(uint32 numBits) {
		uint32 result = 0;
		readBitsToBuffer(&result, numBits);
		return result;
	}

	int32 readSBitLong(int32 numBits) {
		int32 result = readUBitLong(numBits);
		return (result << (32 - numBits)) >> (32 - numBits);
	}

	uint32 readUBitVar() {
		uint32 ret = readUBitLong(6);
		uint32 c = ret;
		switch (ret & (16 | 32)) {
			case 16:
			{
				ret = (ret & 15) | (readUBitLong(4) << 4);
			} break;
			case 32:
			{
				ret = (ret & 15) | (readUBitLong(8) << 4);
			} break;
			case 48:
			{
				uint32 r = (readUBitLong(32 - 4) << 4);
				ret = (ret & 15) | r;
				if (ret >= 4096) {
					int x = 20;
				}
			} break;
		}
		return ret;
	}

	void readBitsToBuffer(void *buffer, const size_t size) {
		for (size_t i = 0; i < size; i++) {
			reinterpret_cast<char*>(buffer)[i / 8] |= readBit() << (i % 8);
		}
	}

	int8 readByte() {
		char result = 0;
		readBitsToBuffer(&result, 8);
		return result;
	}

	void readBytesToBuffer(void *buffer, const size_t size) {
		for (size_t i = 0; i < size; i++) {
			reinterpret_cast<char *>(buffer)[i] = readByte();
		}
	}

	int16 readInt16() {
		int16 result;
		readBytesToBuffer(static_cast<void*>(&result), sizeof(int16));
		return result;
	}

	int32 readInt32() {
		int32 result;
		readBytesToBuffer(static_cast<void*>(&result), sizeof(int32));
		return result;
	}

	int64 readInt64() {
		int64 result;
		readBytesToBuffer(static_cast<void*>(&result), sizeof(int64));
		return result;
	}

	float readFloat() {
		float result;
		readBytesToBuffer(static_cast<void*>(&result), sizeof(float));
		return result;
	}

	std::string readString(const unsigned int &limit) {
		std::string output;
		uint32 currentPos = 0;

		while (1) {
			char val = readByte();
			if (val == 0) {
				break;
			}

			if (currentPos < (limit - 1)) {
				output.push_back(val);
				currentPos++;
			}
		}

		return output;
	}

	int32 readVarInt32() {
		uint32 result = 0;
		int32 count = 0;
		uint32 b;

		do {
			if (count == DataBitStream::MaxVarInt32Bytes) {
				return result;
			}

			b = readByte();
			result |= (b & 0x7F) << (7 * count);
			count++;
		} while (b & 0x80);

		return result;
	}

	uint64 readVarInt64() {
		uint64 result = 0;
		int32 count = 0;
		uint64 b;

		do {
			if (count == DataBitStream::MaxVarInt64Bytes) {
				return result;
			}
			b = readUBitLong(8);
			result |= static_cast<uint64>(b & 0x7F) << (7 * count);
			++count;
		} while (b & 0x80);

		return result;
	}

	float readBitCoord() {
		int32 intval = 0, fractval = 0, signbit = 0;
		float value = 0.0;

		// Read the required integer and fraction flags
		intval = readBit();
		fractval = readBit();

		// If we got either parse them, otherwise it's a zero.
		if (intval || fractval) {
			// Read the sign bit
			signbit = readBit();

			// If there's an integer, read it in
			if (intval) {
				// Adjust the integers from [0..MAX_COORD_VALUE-1] to [1..MAX_COORD_VALUE]
				intval = readUBitLong(COORD_INTEGER_BITS) + 1;
			}

			// If there's a fraction, read it in
			if (fractval) {
				fractval = readUBitLong(COORD_FRACTIONAL_BITS);
			}

			// Calculate the correct floating point value
			value = intval + ((float)fractval * COORD_RESOLUTION);

			// Fixup the sign if negative.
			if (signbit)
				value = -value;
		}

		return value;
	}

	float readBitCoordMP(EBitCoordType coordType) {
		bool bIntegral = (coordType == EBitCoordType::kCW_Integral);
		bool bLowPrecision = (coordType == EBitCoordType::kCW_LowPrecision);

		int32 intval = 0, fractval = 0, signbit = 0;
		float value = 0.0;

		bool bInBounds = readBit() ? true : false;

		if (bIntegral) {
			// Read the required integer and fraction flags
			intval = readBit();
			// If we got either parse them, otherwise it's a zero.
			if (intval) {
				// Read the sign bit
				signbit = readBit();

				// If there's an integer, read it in
				// Adjust the integers from [0..MAX_COORD_VALUE-1] to [1..MAX_COORD_VALUE]
				if (bInBounds) {
					value = static_cast<float>(readUBitLong(COORD_INTEGER_BITS_MP) + 1);
				} else {
					value = static_cast<float>(readUBitLong(COORD_INTEGER_BITS) + 1);
				}
			}
		} else {
			// Read the required integer and fraction flags
			intval = readBit();

			// Read the sign bit
			signbit = readBit();

			// If we got either parse them, otherwise it's a zero.
			if (intval) {
				if (bInBounds) {
					intval = readUBitLong(COORD_INTEGER_BITS_MP) + 1;
				} else {
					intval = readUBitLong(COORD_INTEGER_BITS) + 1;
				}
			}

			// If there's a fraction, read it in
			fractval = readUBitLong(bLowPrecision ? COORD_FRACTIONAL_BITS_MP_LOWPRECISION : COORD_FRACTIONAL_BITS);

			// Calculate the correct floating point value
			value = intval + ((float)fractval * (bLowPrecision ? COORD_RESOLUTION_LOWPRECISION : COORD_RESOLUTION));
		}

		// Fixup the sign if negative.
		if (signbit)
			value = -value;

		return value;
	}

	float readBitFloat() {
		uint32 nvalue = readUBitLong(32);
		return *((float *)&nvalue);
	}

	float readBitNormal() {
		// Read the sign bit
		int32 signbit = readBit();

		// Read the fractional part
		unsigned int fractval = readUBitLong(NORMAL_FRACTIONAL_BITS);

		// Calculate the correct floating point value
		float value = static_cast<float>(fractval) * NORMAL_RESOLUTION;

		// Fixup the sign if negative.
		if (signbit)
			value = -value;

		return value;
	}

	float readBitCellCoord(int bits, EBitCoordType coordType) {
		bool bIntegral = (coordType == EBitCoordType::kCW_Integral);
		bool bLowPrecision = (coordType == EBitCoordType::kCW_LowPrecision);

		int32 intval = 0, fractval = 0;
		float value = 0.0;

		if (bIntegral) {
			value = static_cast<float>(readUBitLong(bits));
		} else {
			intval = readUBitLong(bits);

			// If there's a fraction, read it in
			fractval = readUBitLong(bLowPrecision ? COORD_FRACTIONAL_BITS_MP_LOWPRECISION : COORD_FRACTIONAL_BITS);

			// Calculate the correct floating point value
			value = intval + (static_cast<float>(fractval) * (bLowPrecision ? COORD_RESOLUTION_LOWPRECISION : COORD_RESOLUTION));
		}

		return value;
	}

	~DataBitStream() {
		delete[] m_buffer;
	}

private:
	char *m_buffer;
	uint32 m_sizeBits;
	uint32 m_currentPosition;
};

struct QAngle {
	float x, y, z;

	void init() {
		x = y = z = 0.0f;
	}

	void init(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

struct Vector {
	float x, y, z;

	void init() {
		x = y = z = 0.0f;
	}

	void init(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

struct Prop {
	Prop() {
		numElementos = 0;
		value.vectorValue.init();
	}

	Prop(SendPropType type) : type(type), numElementos(0) {
		value.vectorValue.init();
	}

	SendPropType type;
	union PropValue {
		int32 intValue;
		float floatValue;
		const char *stringValue;
		int64 int64Value;
		Vector vectorValue;
	};

	std::string stringValue;
	
	PropValue value;
	int32 numElementos;
};

struct FlattenedPropEntry {
	FlattenedPropEntry(const CSVCMsg_SendTable::sendprop_t *prop, const CSVCMsg_SendTable::sendprop_t *arrayElementProp)
		: m_prop(prop), m_arrayElementProp(arrayElementProp) {
	}

	const CSVCMsg_SendTable::sendprop_t *m_prop;
	const CSVCMsg_SendTable::sendprop_t *m_arrayElementProp;
};

struct PropEntry {
	PropEntry(Prop propValue, FlattenedPropEntry *flattenedProp) : propValue(propValue), flattenedProp(flattenedProp) {}

	Prop propValue;
	FlattenedPropEntry *flattenedProp;
};

struct EntityEntry {
	uint32 entityID;
	uint32 classID;
	uint32 serialNumber;

	EntityEntry(uint32 entityID, uint32 classID, uint32 serialNumber = 0) {
		this->entityID = entityID;
		this->classID = classID;
		this->serialNumber = serialNumber;

	}

	std::vector<PropEntry> props;
};

struct ExcludeEntry {
	std::string varName;
	std::string DTName;
	std::string DTExcluding;
};

struct ServerClass {
	int nClassID;
	std::string strName;
	std::string strDTName;
	int nDataTable;

	std::vector<FlattenedPropEntry> flattenedProps;
};

struct NetTick {
	uint32 tick; // current tick
	uint32 hostComputationTime; // microseconds
	uint32 hostComputationTimeStdDeviation; // microseconds
	uint32 hostFrameStartTimeStdDeviation; // microseconds
};

struct CommandInfo {
	CommandInfo() {}

	struct Split {

		Split() {
			flags = FDEMO_NORMAL;
			viewOrigin.init();
			viewAngles.init();
			localViewAngles.init();

			// Resampled origin/angles
			viewOrigin2.init();
			viewAngles2.init();
			localViewAngles2.init();
		}

		Split& operator=(const Split &src) {
			if (this == &src) {
				return *this;
			}

			flags = src.flags;
			viewOrigin = src.viewOrigin;
			viewAngles = src.viewAngles;
			localViewAngles = src.localViewAngles;
			viewOrigin2 = src.viewOrigin2;
			viewAngles2 = src.viewAngles2;
			localViewAngles2 = src.localViewAngles2;

			return *this;
		}

		const Vector& getViewOrigin() {
			if (flags & FDEMO_USE_ORIGIN2) {
				return viewOrigin2;
			}
			return viewOrigin;
		}

		const QAngle& getViewAngles() {
			if (flags & FDEMO_USE_ANGLES2) {
				return viewAngles2;
			}
			return viewAngles;
		}
		const QAngle& getLocalViewAngles() {
			if (flags & FDEMO_USE_ANGLES2) {
				return localViewAngles2;
			}
			return localViewAngles;
		}

		void reset() {
			flags = 0;
			viewOrigin2 = viewOrigin;
			viewAngles2 = viewAngles;
			localViewAngles2 = localViewAngles;
		}

		int32 flags;

		// original origin/viewangles
		Vector viewOrigin;
		QAngle viewAngles;
		QAngle localViewAngles;

		// Resampled origin/viewangles
		Vector viewOrigin2;
		QAngle viewAngles2;
		QAngle localViewAngles2;
	};

	void reset() {
		for (int i = 0; i < MAX_SPLITSCREEN_CLIENTS; ++i) {
			u[i].reset();
		}
	}

	Split u[MAX_SPLITSCREEN_CLIENTS];

	CommandInfo parseFromMemory(DataStream &bytes) {
		bytes.readBytesToBuffer(this, sizeof(CommandInfo));
		return *this;
	}

};

struct SequenceInfo {
	int32 seqNrIn;
	int32 seqNrOut;

	SequenceInfo parseFromMemory(DataStream &bytes) {
		seqNrIn = bytes.readInt32();
		seqNrOut = bytes.readInt32();
		return *this;
	}
};

struct DemoHeader {
	char demoFileStamp[8]; // HL2DEMO
	int32 demoProtocol; // DEMO_PROTOCOL
	int32 networkProtocol; // PROTOCOL_VERSION
	char serverName[MAX_OSPATH]; // Name of the server
	char clientName[MAX_OSPATH]; // Name of client (person who recorded the demo)
	char mapName[MAX_OSPATH]; // Name of the map
	char gameDir[MAX_OSPATH]; // Name of game directory (com_gamedir)
	float playblackTime; // time of track
	int32 playblackTicks; // number of ticks on the track
	int32 playblackFrames; // number of frames in track
	int32 signonLength; // length of sigondata in bytes

	const float getTickRate() const {
		return static_cast<float>(this->playblackFrames / this->playblackTime);
	}

	const float getTickTime() const {
		return  static_cast<float>(this->playblackTime / this->playblackFrames);
	}

	DemoHeader parseFromMemory(DataStream &bytes) {
		bytes.readBytesToBuffer(this, sizeof(DemoHeader));
		return *this;
	}
};

struct PlayerInfo {
	uint64 version; // version for future compatibility
	uint64 xuid; // network xuid
	char name[MAX_PLAYER_NAME_LENGTH]; // scoreboard information
	int userID; // local server user ID, unique while server is running
	char guid[SIGNED_GUID_LEN + 1]; // global unique player identifer
	uint32 friendsID; // friends identification number
	char friendsName[MAX_PLAYER_NAME_LENGTH]; // friends name
	bool isFakePlayer; // true, if player is a bot controlled by game.dll
	bool isHLTVProxy; // true if player is the HLTV proxy
	uint32 customFiles[MAX_CUSTOM_FILES]; // custom files CRC for this player
	unsigned char filesDownloaded; // this counter increases each time the server downloaded a new file
	uint32 entityID;

	PlayerInfo parseFromMemory(DataBitStream &bytes) {
		bytes.readBytesToBuffer(this, sizeof(PlayerInfo));

		xuid = SWAP64(xuid);
		userID = SWAP32(userID);
		friendsID = SWAP32(friendsID);

		return *this;
	}
};

struct ServerInfo {
	int32 protocol;
	int32 serverCount;
	bool isDedicated;
	bool isOfficialValveServer;
	bool isHLTV;
	bool isReplay;
	bool isRedirectingToProxyRelay;
	int32 cOS; // L = Linux, W = Windows
	uint32 mapCRC;
	uint32 clientCRC;
	uint32 stringTableCRC;
	int32 maxClients;
	int32 maxClasses;
	int32 playerSlot;
	float tickInterval;
	std::string gameDir;
	std::string mapName;
	std::string mapGroupName;
	std::string skyName;
	std::string hostName;
	uint32 publicIP;
	uint64 ugcMapID;
};

std::ostream& operator<<(std::ostream &out, const DemoHeader &header);
std::ostream& operator<<(std::ostream &out, const PlayerInfo &player);
std::ostream& operator<<(std::ostream &out, const ServerInfo &serverInfo);

Prop* DecodeProp(DataBitStream &data, FlattenedPropEntry *flattenedProp, uint32 classID, int fieldIndex);

static int32 Int_Decode(DataBitStream &data, const CSVCMsg_SendTable::sendprop_t *sendProp) {
	int32 flags = sendProp->flags();

	if (flags & SPROP_VARINT) {
		if (flags & SPROP_UNSIGNED) {
			return data.readVarInt32();
		} else {
			return data.readSignedVarInt32();
		}
	} else {
		if (flags & SPROP_UNSIGNED) {
			return data.readUBitLong(sendProp->num_bits());
		} else {
			return data.readSBitLong(sendProp->num_bits());
		}
	}
}

static inline bool DecodeSpecialFloat(DataBitStream &data, const CSVCMsg_SendTable::sendprop_t *sendProp, float &val) {
	int flags = sendProp->flags();

	if (flags & SPROP_COORD) {
		val = data.readBitCoord();
		return true;
	} else if (flags & SPROP_COORD_MP) {
		val = data.readBitCoordMP(EBitCoordType::kCW_None);
		return true;
	} else if (flags & SPROP_COORD_MP_LOWPRECISION) {
		val = data.readBitCoordMP(EBitCoordType::kCW_LowPrecision);
		return true;
	} else if (flags & SPROP_COORD_MP_INTEGRAL) {
		val = data.readBitCoordMP(EBitCoordType::kCW_Integral);
		return true;
	} else if (flags & SPROP_NOSCALE) {
		val = data.readBitFloat();
		return true;
	} else if (flags & SPROP_NORMAL) {
		val = data.readBitNormal();
		return true;
	} else if (flags & SPROP_CELL_COORD) {
		val = data.readBitCellCoord(sendProp->num_bits(), EBitCoordType::kCW_None);
		return true;
	} else if (flags & SPROP_CELL_COORD_LOWPRECISION) {
		val = data.readBitCellCoord(sendProp->num_bits(), EBitCoordType::kCW_LowPrecision);
		return true;
	} else if (flags & SPROP_CELL_COORD_INTEGRAL) {
		val = data.readBitCellCoord(sendProp->num_bits(), EBitCoordType::kCW_Integral);
		return true;
	}

	return false;
}

static float Float_Decode(DataBitStream &data, const CSVCMsg_SendTable::sendprop_t *sendProp) {
	float result = 0.0f;
	unsigned long dwInterp;

	// Check for special flags..
	if (DecodeSpecialFloat(data, sendProp, result)) {
		return result;
	}

	dwInterp = data.readUBitLong(sendProp->num_bits());
	result = static_cast<float>(dwInterp) / ((1 << sendProp->num_bits()) - 1);
	result = sendProp->low_value() + (sendProp->high_value() - sendProp->low_value()) * result;
	return result;
}

static void Vector_Decode(DataBitStream &data, const CSVCMsg_SendTable::sendprop_t *sendProp, Vector &vect) {
	vect.x = Float_Decode(data, sendProp);
	vect.y = Float_Decode(data, sendProp);

	// Don't read in the third component for normals
	if ((sendProp->flags() & SPROP_NORMAL) == 0) {
		vect.z = Float_Decode(data, sendProp);
	} else {
		int signbit = data.readBit();

		float v0v0v1v1 = vect.x * vect.x + vect.y * vect.y;
		if (v0v0v1v1 < 1.0f) {
			vect.z = sqrtf(1.0f - v0v0v1v1);
		} else {
			vect.z = 0.0f;
		}

		if (signbit) {
			vect.z *= -1.0f;
		}
	}
}

static void VectorXY_Decode(DataBitStream &data, const CSVCMsg_SendTable::sendprop_t *sendProp, Vector &vect) {
	vect.x = Float_Decode(data, sendProp);
	vect.y = Float_Decode(data, sendProp);
}

static std::string String_Decode(DataBitStream &data, const CSVCMsg_SendTable::sendprop_t *sendProp) {
	// Read it in.
	int len = data.readUBitLong(DT_MAX_STRING_BITS);

	char *tempStr = new char[len + 1];

	if (len >= DT_MAX_STRING_BUFFERSIZE) {
		std::cerr << "String_Decode: String_Decode(" << sendProp->var_name() << ") invalid length (" << len << ")" << std::endl;
		len = DT_MAX_STRING_BUFFERSIZE - 1;
	}

	data.readBytesToBuffer(tempStr, len);
	tempStr[len] = 0;
	return std::string(tempStr);
}

static int64 Int64_Decode(DataBitStream &data, const CSVCMsg_SendTable::sendprop_t *sendProp) {
	if (sendProp->flags() & SPROP_VARINT) {
		if (sendProp->flags() & SPROP_UNSIGNED) {
			return (int64)data.readVarInt64();
		} else {
			return data.readSignedVarInt64();
		}
	} else {
		uint32 highInt = 0;
		uint32 lowInt = 0;
		bool bNeg = false;
		if (!(sendProp->flags() & SPROP_UNSIGNED)) {
			bNeg = data.readBit() != 0;
			lowInt = data.readUBitLong(32);
			highInt = data.readUBitLong(sendProp->num_bits() - 32 - 1);
		} else {
			lowInt = data.readUBitLong(32);
			highInt = data.readUBitLong(sendProp->num_bits() - 32);
		}

		int64 temp;

		uint32 *pInt = (uint32*)&temp;
		*pInt++ = lowInt;
		*pInt = highInt;

		if (bNeg) {
			temp = -temp;
		}

		return temp;
	}
}

static Prop* Array_Decode(DataBitStream &data, FlattenedPropEntry *flattenedProp, int32 numElements, uint32 classID, int32 fieldIndex) {
	int maxElements = numElements;
	int numBits = 1;
	while ((maxElements >>= 1) != 0) {
		numBits++;
	}

	int32 elements = data.readUBitLong(numBits);

	Prop *result = 0;
	result = new Prop[numElements];

	for (int32 i = 0; i < elements; i++) {
		FlattenedPropEntry temp(flattenedProp->m_arrayElementProp, 0);
		Prop *elementResult = DecodeProp(data, &temp, classID, fieldIndex);
		result[i] = *elementResult;
		delete elementResult;
		result[i].numElementos = numElements - i;
	}

	return result;
}

struct CSGOTeam {
	uint32 teamNumber;
	uint32 scoreTotal;
	uint32 scoreFirstHalf;
	uint32 scoreSecondHalf;
	uint32 scoreOvertime;
	uint32 clanID;
	bool surrendered;
	std::string clanName;
	std::string teamName;
	std::string teamFlagImage;
	std::string teamLogoImage;
	CSGOTeamType type;
};

struct CSGOPlayer {
	uint32 entityID;
	std::string name;
	uint64 xuid;
	bool isFakePlayer;
	bool isHLTVProxy;
	Vector position;
	Vector eyeAngles;
	bool isConnected;
	bool isObserver;
	bool hasKit;
	int32 health;
	int32 armor;
	int32 kills;
	int32 deaths;
	int32 assists;
	int32 score;
	int32 mvps;
	std::string clanTag;
	uint32 teamNumber;
	PlayerInfo _playerInfo; // just in case

	bool isAlive() const {
		return (health > 0) ? true : false;
	}
};

class CSGOSimpleDemo {
private:
	DataBuffer *m_buffer;
	DataStream *m_stream;
	std::string m_fileName;
	DemoHeader m_header;
	bool m_demoOpen;
	int32 m_inGameTick;
	int32 m_currentTick;
	int32 m_serverClassBits;
	CommandInfo m_commandInfo;
	std::unordered_map<uint32, CSGOPlayer> m_players;
	std::unordered_map<std::string, std::string> m_conVars;
	bool m_demoParsed;
	ServerInfo m_serverInfo;
	std::vector<NetTick> m_netTicks;
	std::vector<std::string> m_modelPrecache;
	std::unordered_map<uint32, CSGOTeam> m_teams;
	std::unordered_map<uint32, uint8*> m_instanceBaselines;

	std::vector<CSVCMsg_SendTable> m_dataTables;
	std::vector<ServerClass> m_serverClasses;
	std::vector<ExcludeEntry> m_excludedEntries;
	std::vector<EntityEntry> m_entities;


	bool m_parsePacketEntities;
	bool m_parseGameEvents;
public:
	CSGOSimpleDemo();
	CSGOSimpleDemo(const std::string &fileName);
	bool open(const std::string &fileName);

	bool isDemoParsed() { return m_demoParsed; }

	DemoHeader getHeader() const { return m_header; }
	ServerInfo getServerInfo() const { return m_serverInfo; }
	int32 getCurrentTick() const { return m_currentTick; }
	NetTick getCurrentNetTick() const { return m_netTicks.back(); }
	std::vector<NetTick> getAllNetTick() const { return m_netTicks; }

	template<typename T>
	T getConVar(const std::string &conVarName);

	void parseAll();
	bool parseNextTick();

	void setParsePacketEntities(bool parse) { m_parsePacketEntities = parse; }
	void setParseGameEvents(bool parse) { m_parseGameEvents = parse; }
	bool isParsingPacketEntities() const { return m_parsePacketEntities; }
	bool isParsingGameEvents() const { return m_parseGameEvents; }

	uint32 getNumberPlayers() const { return m_players.size(); }
	std::vector<CSGOPlayer> getParticipants() const;
	std::vector<CSGOPlayer> getCTPlayers();
	std::vector<CSGOPlayer> getTPlayers();
	std::vector<CSGOPlayer> getSpectators();
	CSGOTeam getCTTeam() const;
	CSGOTeam getTTeam() const;
	CSGOTeam getTeamByNumber(uint32 teamNumber);

	~CSGOSimpleDemo();
private:
	bool parseTick();
	bool parseDataTables();
	void parseUserInfo(DataBitStream &data, const uint32 &entityID);
	void parseStringTables();
	void parseStringTable(const std::string &tableName, DataBitStream &stream);
	void readRawData(char *buffer, int bufferSize);
	void parseUserMessage(CSVCMsg_UserMessage &message);
	void parseSetConVar(CNETMsg_SetConVar &setConVar);
	void parseServerInfo(CSVCMsg_ServerInfo &serverInfo);
	void parseGameEvent(CSVCMsg_GameEvent &event);
	void parseNetTick(CNETMsg_Tick &netTick);
	void parsePacketEntities(CSVCMsg_PacketEntities &packetEntities);
	void removeEntity(int32 entityID);
	int32 readFieldIndex(DataBitStream &data, bool newWay, int32 lastIndex);
	FlattenedPropEntry* getSendPropByIndex(uint32 classID, uint32 index);
	void processProp(const CSVCMsg_SendTable &table, const EntityEntry &entity, const PropEntry &propEntry);
	EntityEntry* getEntity(int32 entityID);
	EntityEntry* addEntity(int32 entityID, uint32 classID, uint32 serialNumber, DataBitStream &data);
	EntityEntry* updateEntity(EntityEntry *entity, DataBitStream &data);
	void parseEntity(EntityEntry *entity, DataBitStream &data);
	void parsePacket();
	CSVCMsg_SendTable* getTableByName(const std::string name);
	CSVCMsg_SendTable* getTableByClassID(uint32 classID);
	bool isPropExcluded(CSVCMsg_SendTable &table, const CSVCMsg_SendTable::sendprop_t &checkSendProp);
	void flattenDataTable(int32 nServerClass);
	void gatherProps(CSVCMsg_SendTable *table, int32 nServerClass);
	void gatherPropsIterateProps(CSVCMsg_SendTable *table, int32 nServerClass, std::vector<FlattenedPropEntry> *flattenedProps);
	void gatherExcludes(CSVCMsg_SendTable *table);
};


template<typename T>
T CSGOSimpleDemo::getConVar(const std::string &conVarName) {
	T result;

	if (!m_demoOpen) {
		std::cerr << "CSGOSimpleDemo::getConVar: Demo not open" << std::endl;
		return T;
	}

	auto conVar = m_conVars.find(conVarName);

	if (conVar != m_conVars.end()) {
		std::stringstream value(conVar->second);

		if (!(value >> result)) {
			std::cerr << "CSGOSimpleDemo::getConVar: Could not convert to the type specified" << std::endl;
		}
	}

	return result;
}


#endif

