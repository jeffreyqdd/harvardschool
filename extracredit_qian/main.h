class SafeArray
{
private:
    int *m_startArr;
    int m_size;
public:
    SafeArray(); //default
    SafeArray(initializer_list<int>);
    SafeArray(const SafeArray &); //copy

    void init();
    void addItems(int, int=0);
    int at(int);
    void put(int,int);
    void put(int, int*, int);
    void copyTo(vector<int>&) const;
    int size();
    void clear();

    ~SafeArray();
};


class ArrayBoundsException
{
private:
    SafeArray* m_s;
    int m_index;

public:
    ArrayBoundsException(SafeArray* arr, int index): m_s(arr), m_index(index) //constructor
    {}

    string what() const //returns a string regarding safearray size and the index.
    {
        return "Out of bounds access occured. Array size is: " + to_string(m_s -> size() )
             + ". Attempted access of index: " + to_string(m_index) + ". Will return 0 instead.";
    }
};


//safe array method definitions

void SafeArray::init()
{
    try
    {
        m_startArr = new int[0];
    }
    catch(const exception& e)
    {
        cout << e.what() << '\n';
    }
}

SafeArray::SafeArray() //default
{
    init();
}

SafeArray::SafeArray(initializer_list<int> l) //initializes using initializer list.
{
    m_startArr = new int[l.size()];
    m_size = l.size();
    copy(l.begin(), l.end(), m_startArr);
}

SafeArray::SafeArray(const SafeArray &obj) //copy
{
    m_startArr = new int[obj.m_size];

    for(int *i = m_startArr,*j = obj.m_startArr, o = 0; o < m_size ; i++, j++, o++)
    {
        *j = *i;
    }

}
void SafeArray::addItems(int howMany, int value) //append
{
    int *newArr; //temporary storage
    newArr = new int[m_size + howMany];

    copy(m_startArr, m_startArr + m_size, newArr);

    for(int i = m_size; i < m_size+howMany; i++) //fill in remaining values
    {
        newArr[i] = value;
    }

    //replace
    //m_startArr = nullptr;
    delete[] m_startArr;

    m_startArr = newArr;
    m_size += howMany; //update size

}
int SafeArray::at(int index) //get at indexx
{
    try
    {
        if(index > m_size - 1 || index < 0)
            throw ArrayBoundsException(this , index);

        return m_startArr[index];
    }
    catch(const ArrayBoundsException& a)
    {
        cout << a.what() << '\n';
        return 0;
    }
    
}

void SafeArray::put(int index,int data) //replace
{
    try
    {
        if(index > m_size - 1 || index < 0)
            throw ArrayBoundsException(this , index);

        m_startArr[index] = data;    
    }
    catch(const ArrayBoundsException& a)
    {
        cout << a.what() << '\n';
    }
    
}
void SafeArray::put(int index, int* pArr, int howmany) //replace starting at index
{
    try
    {
        for(int i = index; i < index + howmany; i++)
        {
            if(i < 0 || i > m_size) throw ArrayBoundsException(this , index);

            m_startArr[i] = pArr[i-index];
        }
    }
    catch(const ArrayBoundsException& a)
    {
        cout << a.what() << '\n';
    }
}
void SafeArray::copyTo(vector<int>& v) const//copy safearray to vector
{
    v.clear();
    for(int i = 0; i < m_size; i++)
        v.push_back(m_startArr[i]);
        
}
int SafeArray::size() //return size
{   
    return m_size;
}
void SafeArray::clear() //deletes everything and resets back to normal.
{
    delete[] m_startArr;

    m_startArr = nullptr;
    m_size = 0;

    init();

}
SafeArray::~SafeArray() //destructor
{
    cout << "deleting SafeArray" <<endl;
    delete[] m_startArr;
}

struct Text
{
    string word;
    int freq;

    bool operator<(const Text& t) const
    {
        if(freq == t.freq) //if same frequency
            return word < t.word; //alphabetical
        return freq > t.freq; //descending
    }
};