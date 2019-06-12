#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <QSize>
#include <QVector>


template<typename T>
class Array2D
{
public:
    Array2D()
        : m_data(nullptr)
    {
        init(0, 0);
    }

    Array2D(uint32_t width, uint32_t height)
        : m_data(nullptr)
    {
        init(width, height);
    }

    Array2D(const Array2D& other)
        : m_data(nullptr)
    {
        this->operator=(other);
    }

    virtual ~Array2D()
    {
        clear();
    }
protected:
    void init(uint32_t width, uint32_t height)
    {
        clear(true);

        m_width  = width;
        m_height = height;

        if (0 != m_width && 0 != m_height)
            m_data = new T[m_width*m_height];
   }

    void clear(bool isInitialization)
    {
        if (!isInitialization)
            delete[] m_data;

        m_data   = nullptr;
        m_width  = 0;
        m_height = 0;
    }

public:
   void clear()
    {
        clear(false);
    }

    void operator =(const Array2D& otherArray2D)
    {
        if (&otherArray2D == this)
            return;

        clear();

        m_width  = otherArray2D.m_width;
        m_height = otherArray2D.m_height;

        if (0 != m_width && 0 != m_height)
            m_data = new T[otherArray2D.square()];

        copyData(otherArray2D);
    }

public:
    inline void resize(const QSize& newSize)
    {
        return resize(newSize.width(), newSize.height());
    }

    inline void resize(const uint32_t height)
    {
        return resize(m_width, height);
    }

    void resize(const uint32_t width, const uint32_t height)
    {
        if (0 == width || 0 == height)
        {
            clear();
            return;
        }

        T* newData = new T[width*height];
        copyData(newData, m_data, square());
        m_data   = newData;
        m_width  = width;
        m_height = height;
    }

    int appendLine(const QVector<T>& newLine)
    {
        return appendLine(newLine.data());
    }

    int appendLine(const T* newLine)
    {
        int result = m_height;

        resize(m_height+1);
        copyData(m_data +result*m_width, newLine, m_width);

        return result;
    }

public:
    void setValues(T value)
    {
        for (uint32_t i = 0; i < square(); ++i)
            m_data[i] = value;
    }

public:
    inline bool isEmpty() const
    {
        return (nullptr == m_data
                || 0 == m_width
                || 0 == m_height);
    }

    inline uint32_t square() const
    {
        return m_width * m_height;
    }

    inline QSize size() const
    {
        return QSize(m_width, m_height);
    }

public:
    inline const T& at(uint32_t line, uint32_t column) const
    {
        return at_core(line, column);
    }

    inline T& at(uint32_t line, uint32_t column)
    {
        return at_core(line, column);
    }

    inline const T& at(int line, int column) const
    {
        return at_core(static_cast<uint32_t>(line), static_cast<uint32_t>(column));
    }

    inline T& at(int line, int column)
    {
        return at_core(static_cast<uint32_t>(line), static_cast<uint32_t>(column));
    }


protected:
    T& at_core(uint32_t line, uint32_t column) const
    {
        if (isEmpty())
            throw new std::exception("Array2D::at: this array is empty. Call isEmpty() before calling at().");

        if (line < 0 || line >= m_width)
            throw new std::exception("Array2D::at: width is out of range.");
        if (column < 0 || column >= m_height)
            throw new std::exception("Array2D::at: height is out of range.");

        T& elem = m_data[line*m_height + column];
        return elem;
    }

    inline T* copyData(const Array2D& fromArray)
    {
        return copyData(fromArray.m_data, fromArray.square());
    }

    T* copyData(const T* fromData, uint32_t dataLength)
    {
        dataLength = dataLength <= square() ? dataLength : square();
        return Array2D::copyData(this->m_data, fromData, dataLength);
    }

    static T* copyData(T* toData, const T* fromData, uint32_t length)
    {
        if (nullptr == toData || nullptr == fromData)
            return toData;
//~        if (nullptr == toData)
//~            throw new std::exception("Array2D::copy: 'T* toData' is NULL");
//~        if (nullptr == fromData)
//~            throw new std::exception("Array2D::copy: 'const T* fromData' is NULL");
        return static_cast<T*>( std::memcpy(toData, fromData, length*sizeof(T)) );
    }

private:
    T*       m_data;
    uint32_t m_width;
    uint32_t m_height;
};

#endif // ARRAY2D_H
