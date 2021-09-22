#pragma once

// begin of namespace RF =========================================================================
namespace RF {

typedef unsigned char CData;
typedef unsigned short int SData;
typedef uint32_t IData;
typedef unsigned long QData;

using WData = IData;
using WDataInP = const WData*;  ///< 'bit' of >64 packed bits as array input to a function
using WDataOutP = WData*;  ///< 'bit' of >64 packed bits as array output from a function

template <typename DType> struct DataLoc final {
    size_t memloc;
    size_t size;
    explicit DataLoc(size_t memloc, size_t size = 1)
        : memloc{memloc}
        , size{size} {}
};

typedef DataLoc<CData> CDataLoc;
typedef DataLoc<SData> SDataLoc;
typedef DataLoc<QData> QDataLoc;
typedef DataLoc<IData> IDataLoc;

//#define RF_SIG8(name, msb, lsb) CDataLoc name  ///< Declare signal, 1-8 bits
//#define RF_SIG16(name, msb, lsb) SDataLoc name  ///< Declare signal, 9-16 bits
//#define RF_SIG64(name, msb, lsb) QDataLoc name  ///< Declare signal, 33-64 bits
//#define RF_SIG(name, msb, lsb) IDataLoc name  ///< Declare signal, 17-32 bits
//#define RF_SIGW(name, msb, lsb, words) IDataLoc name  ///< Declare signal, 65+ bits
#define RF_IN8(name, msb, lsb) CDataLoc name  ///< Declare input signal, 1-8 bits
#define RF_IN16(name, msb, lsb) SDataLoc name  ///< Declare input signal, 9-16 bits
#define RF_IN64(name, msb, lsb) QDataLoc name  ///< Declare input signal, 33-64 bits
#define RF_IN(name, msb, lsb) IDataLoc name  ///< Declare input signal, 17-32 bits
#define RF_INW(name, msb, lsb, words) IDataLoc name  ///< Declare input signal, 65+ bits
#define RF_INOUT8(name, msb, lsb) CDataLoc name  ///< Declare bidir signal, 1-8 bits
#define RF_INOUT16(name, msb, lsb) SDataLoc name  ///< Declare bidir signal, 9-16 bits
#define RF_INOUT64(name, msb, lsb) QDataLoc name  ///< Declare bidir signal, 33-64 bits
#define RF_INOUT(name, msb, lsb) IDataLoc name  ///< Declare bidir signal, 17-32 bits
#define RF_INOUTW(name, msb, lsb) IDataLoc name  ///< Declare bidir signal, 65+ bits
#define RF_OUT8(name, msb, lsb) CDataLoc name  ///< Declare output signal, 1-8 bits
#define RF_OUT16(name, msb, lsb) SDataLoc name  ///< Declare output signal, 9-16 bits
#define RF_OUT64(name, msb, lsb) QDataLoc name  ///< Declare output signal, 33-64bits
#define RF_OUT(name, msb, lsb) IDataLoc name  ///< Declare output signal, 17-32 bits
#define RF_OUTW(name, msb, lsb, words) IDataLoc name  ///< Declare output signal, 65+ bits

template <class T_Value, std::size_t T_Depth> struct RfUnpacked final {

    T_Value m_array[T_Depth];

    __device__ T_Value& operator[](size_t index) { return m_array[index]; }
    __device__ const T_Value& operator[](size_t index) const { return m_array[index]; }
};

template <std::size_t T_Words> struct RfWide final {
    IData m_storage[T_Words];

    __device__ const IData& operator[](size_t index) const { return m_storage[index]; };
    __device__ IData& operator[](size_t index) { return m_storage[index]; };
    __device__ operator WDataOutP() { return &m_storage[0]; }
    __device__ operator WDataInP() const { return &m_storage[0]; }

    // METHODS
    __device__ const IData& at(size_t index) const { return m_storage[index]; }
    __device__ IData& at(size_t index) { return m_storage[index]; }
    WData* data() { return &m_storage[0]; }
    const WData* data() const { return &m_storage[0]; }
    // bool operator<(const VlWide<T_Words>& rhs) const {
    // return VL_LT_W(T_Words, data(), rhs.data());
    //}
};

//# define RF_LIKELY(x) __builtin_expect(!!(x), 1)
//# define RF_UNLIKELY(x) __builtin_expect(!!(x), 0)

//#define RF_MT_SAFE
//#define RF_BYTESIZE 8  ///< Bits in a CData / byte
//#define RF_SHORTSIZE 16  ///< Bits in a SData / short
//#define RF_IDATASIZE 32  ///< Bits in a IData / word
//#define RF_QUADSIZE 64  ///< Bits in a QData / quadword
//#define RF_EDATASIZE 32  ///< Bits in a EData (WData entry)
//#define RF_EDATASIZE_LOG2 5  ///< log2(RF_EDATASIZE)
//#define RF_CACHE_LINE_BYTES 64  ///< Bytes in a cache line (for alignment)

//#define RF_SIZEBITS_I (RF_IDATASIZE - 1)  ///< Bit mask for bits in a word
//#define RF_SIZEBITS_Q (RF_QUADSIZE - 1)  ///< Bit mask for bits in a quad
//#define RF_SIZEBITS_E (RF_EDATASIZE - 1)  ///< Bit mask for bits in a quad

///// Return mask for words with 1's where relevant bits are (0=all bits)
//#define RF_MASK_I(nbits) (((nbits) & RF_SIZEBITS_I) ? ((1U << ((nbits) & RF_SIZEBITS_I)) - 1) :
//~0)
///// Return mask for quads with 1's where relevant bits are (0=all bits)
//#define RF_MASK_Q(nbits) \
    //(((nbits) & RF_SIZEBITS_Q) ? ((1ULL << ((nbits) & RF_SIZEBITS_Q)) - 1ULL) : ~0ULL)
///// Return mask for EData with 1's where relevant bits are (0=all bits)
//#define RF_MASK_E(nbits) RF_MASK_I(nbits)

///// Return number of bytes argument-number of bits needs (1 bit=1 byte)
//#define RF_BYTES_I(nbits) (((nbits) + (RF_BYTESIZE - 1)) / RF_BYTESIZE)
///// Return Words/EDatas in argument-number of bits needs (1 bit=1 word)
//#define RF_WORDS_I(nbits) (((nbits) + (RF_EDATASIZE - 1)) / RF_EDATASIZE)
//// Number of Words/EDatas a quad requires
//#define RF_WQ_WORDS_E RF_WORDS_I(RF_QUADSIZE)

//#define RF_BITWORD_I(bit) ((bit) / RF_IDATASIZE)  ///< Word number for sv DPI vectors
//#define RF_BITWORD_E(bit) ((bit) >> RF_EDATASIZE_LOG2)  ///< Word number for a wide quantity
//#define RF_BITBIT_I(bit) ((bit) & RF_SIZEBITS_I)  ///< Bit number for a bit in a long
//#define RF_BITBIT_Q(bit) ((bit) & RF_SIZEBITS_Q)  ///< Bit number for a bit in a quad
//#define RF_BITBIT_E(bit) ((bit) & RF_SIZEBITS_E)  ///< Bit number for a bit in a EData

//#define RF_CLEAN_II(obits, lbits, lhs) ((lhs)&RF_MASK_I(obits))
//#define RF_CLEAN_QQ(obits, lbits, lhs) ((lhs)&RF_MASK_Q(obits))

//#define RF_SET_WQ(owp, data) \
    //do { \
        //(owp)[0] = static_cast<IData>(data); \
        //(owp)[1] = static_cast<IData>((data) >> RF_EDATASIZE); \
    //} while (false)

//#define RF_SET_WI(owp, data) \
    //do { \
        //(owp)[0] = static_cast<IData>(data); \
        //(owp)[1] = 0; \
    //} while (false)

//#define RF_SET_QW(lwp) \
    //((static_cast<QData>((lwp)[0])) \
     //| (static_cast<QData>((lwp)[1]) << (static_cast<QData>(RF_EDATASIZE))))

//#define RF_SET_QII(ld, rd) ((static_cast<QData>(ld) << 32ULL) | static_cast<QData>(rd))

//// Comment tag that Function is pure (and thus also VL_MT_SAFE)
//#define RF_PURE

//// INTERNAL: Stuff large LHS bit 0++ into OUTPUT at specified offset
//// lwp may be "dirty"
//__device__
// static inline void _rf_insert_WW(int, WDataOutP owp, WDataInP lwp, int hbit, int lbit,
// int rbits = 0) VL_MT_SAFE {
// int hoffset = RF_BITBIT_E(hbit);
// int loffset = RF_BITBIT_E(lbit);
// int roffset = RF_BITBIT_E(rbits);
// int lword = RF_BITWORD_E(lbit);
// int hword = RF_BITWORD_E(hbit);
// int rword = RF_BITWORD_E(rbits);
// int words = RF_WORDS_I(hbit - lbit + 1);
//// Cleaning mask, only applied to top word of the assignment.  Is a no-op
//// if we don't assign to the top word of the destination.
// EData cleanmask = hword == rword ? RF_MASK_E(roffset) : RF_MASK_E(0);

// if (hoffset == RF_SIZEBITS_E && loffset == 0) {
//// Fast and common case, word based insertion
// for (int i = 0; i < (words - 1); ++i) owp[lword + i] = lwp[i];
// owp[hword] = lwp[words - 1] & cleanmask;
//} else if (loffset == 0) {
//// Non-32bit, but nicely aligned, so stuff all but the last word
// for (int i = 0; i < (words - 1); ++i) owp[lword + i] = lwp[i];
//// Know it's not a full word as above fast case handled it
// EData hinsmask = (RF_MASK_E(hoffset - 0 + 1));
// owp[hword] = (owp[hword] & ~hinsmask) | (lwp[words - 1] & (hinsmask & cleanmask));
//} else {
// EData hinsmask = (RF_MASK_E(hoffset - 0 + 1)) << 0;
// EData linsmask = (RF_MASK_E((RF_EDATASIZE - 1) - loffset + 1)) << loffset;
// int nbitsonright = RF_EDATASIZE - loffset;  // bits that end up in lword (know loffset!=0)
//// Middle words
// for (int i = 0; i < words; ++i) {
//{  // Lower word
// int oword = lword + i;
// EData d = lwp[i] << loffset;
// EData od = (owp[oword] & ~linsmask) | (d & linsmask);
// if (oword == hword) {
// owp[oword] = (owp[oword] & ~hinsmask) | (od & (hinsmask & cleanmask));
//} else {
// owp[oword] = od;
//}
//}
//{  // Upper word
// int oword = lword + i + 1;
// if (oword <= hword) {
// EData d = lwp[i] >> nbitsonright;
// EData od = (d & ~linsmask) | (owp[oword] & linsmask);
// if (oword == hword) {
// owp[oword] = (owp[oword] & ~hinsmask) | (od & (hinsmask & cleanmask));
//} else {
// owp[oword] = od;
//}
//}
//}
//}
//}
//}

//__device__
// static inline void _rf_insert_WQ(int obits, WDataOutP owp, QData ld, int hbit, int lbit,
// int rbits = 0) VL_MT_SAFE {
// WData lwp[RF_WQ_WORDS_E];
// RF_SET_WQ(lwp, ld);
//_rf_insert_WW(obits, owp, lwp, hbit, lbit, rbits);
//}

//__device__
// static inline WDataOutP RF_ADD_W(int words, WDataOutP owp, WDataInP lwp, WDataInP rwp)
// RF_MT_SAFE { QData carry = 0; for (int i = 0; i < words; ++i) { carry = carry +
// static_cast<QData>(lwp[i]) + static_cast<QData>(rwp[i]); owp[i] = (carry & 0xffffffffULL); carry
// = (carry >> 32ULL) & 0xffffffffULL;
//}
//// Last output word is dirty
// return owp;
//}

//__device__
// static inline WDataOutP RF_EXTEND_WI(int obits, int, WDataOutP owp, IData ld) RF_MT_SAFE {
//// Note for extracts that obits != lbits
// owp[0] = ld;
// for (int i = 1; i < RF_WORDS_I(obits); ++i) owp[i] = 0;
// return owp;
//}

//__device__
// static inline WDataOutP RF_EXTEND_WQ(int obits, int, WDataOutP owp, QData ld) RF_MT_SAFE {
// RF_SET_WQ(owp, ld);
// for (int i = VL_WQ_WORDS_E; i < RF_WORDS_I(obits); ++i) owp[i] = 0;
// return owp;
//}

//__device__
// static inline WDataOutP RF_EXTEND_WW(int obits, int lbits, WDataOutP owp,
// WDataInP lwp) VL_MT_SAFE {
// for (int i = 0; i < RF_WORDS_I(lbits); ++i) owp[i] = lwp[i];
// for (int i = RF_WORDS_I(lbits); i < RF_WORDS_I(obits); ++i) owp[i] = 0;
// return owp;
//}

//__device__
// static inline WDataOutP RF_SHIFTL_WWI(int obits, int, int, WDataOutP owp, WDataInP lwp,
// IData rd) RF_MT_SAFE {
// int word_shift = RF_BITWORD_E(rd);
// int bit_shift = RF_BITBIT_E(rd);
// if (rd >= static_cast<IData>(obits)) {  // rd may be huge with MSB set
// for (int i = 0; i < RF_WORDS_I(obits); ++i) owp[i] = 0;
//} else if (bit_shift == 0) {  // Aligned word shift (<<0,<<32,<<64 etc)
// for (int i = 0; i < word_shift; ++i) owp[i] = 0;
// for (int i = word_shift; i < RF_WORDS_I(obits); ++i) owp[i] = lwp[i - word_shift];
//} else {
// for (int i = 0; i < RF_WORDS_I(obits); ++i) owp[i] = 0;
//_rf_insert_WW(obits, owp, lwp, obits - 1, rd);
//}
// return owp;
//}

//__device__
// static inline WDataOutP RF_SHIFTL_WWW(int obits, int lbits, int rbits, WDataOutP owp, WDataInP
// lwp, WDataInP rwp) RF_MT_SAFE {
// for (int i = 1; i < RF_WORDS_I(rbits); ++i) {
// if (RF_UNLIKELY(rwp[i])) {  // Huge shift 1>>32 or more
// return RF_ZERO_W(obits, owp);
//}
//}
// return RF_SHIFTL_WWI(obits, lbits, 32, owp, lwp, rwp[0]);
//}

//__device__
// static inline WDataOutP RF_SHIFTL_WWQ(int obits, int lbits, int rbits, WDataOutP owp, WDataInP
// lwp, QData rd) RF_MT_SAFE {
// WData rwp[RF_WQ_WORDS_E];
// RF_SET_WQ(rwp, rd);
// return RF_SHIFTL_WWW(obits, lbits, rbits, owp, lwp, rwp);
//}

////cuda does not support string
//__device__
// void RF_WRITEF(const char* formatp, ...) VL_MT_SAFE {
////static VL_THREAD_LOCAL std::string t_output;  // static only for speed
////t_output = "";
////va_list ap;
////va_start(ap, formatp);
////_vl_vsformat(t_output, formatp, ap);
////va_end(ap);

////RF_PRINTF_MT("%s", t_output.c_str());
//}

//__device__
// static inline QData RF_SHIFTRS_QQI(int obits, int lbits, int, QData lhs, IData rhs) RF_PURE {
// QData sign = -(lhs >> (lbits - 1));
// QData signext = ~(RF_MASK_Q(lbits) >> rhs);
// return (lhs >> rhs) | (sign & RF_CLEAN_QQ(obits, obits, signext));
//}
//
}  // namespace RF
