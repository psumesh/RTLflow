
template <class T_Value, std::size_t T_Depth, std::size_t Num_Testbenches> 
struct RfUnpacked final {

  T_Value* m_array;

  __device__ T_Value& operator[](size_t index) { return m_array[Num_Testbenches * index]; }
  __device__ const T_Value& operator[](size_t index) const { return m_array[Num_Testbenches * index]; }

};

template <std::size_t T_Words, std::size_t Num_Testbenches> 
struct RfWide final {
    EData* m_storage;

 __device__  const EData& operator[](size_t index) const { return m_storage[Num_Testbenches * index]; };
 __device__  EData& operator[](size_t index) { return m_storage[Num_Testbenches * index]; };
    //operator WDataOutP() { return &m_storage[0]; }
    //operator WDataInP() const { return &m_storage[0]; }

    // METHODS
 __device__   const EData& at(size_t index) const { return m_storage[Num_Testbenches * index]; }
 __device__   EData& at(size_t index) { return m_storage[Num_Testbenches * index]; }
    //WData* data() { return &m_storage[0]; }
    //const WData* data() const { return &m_storage[0]; }
    //bool operator<(const VlWide<T_Words>& rhs) const {
        //return VL_LT_W(T_Words, data(), rhs.data());
    //}
};
