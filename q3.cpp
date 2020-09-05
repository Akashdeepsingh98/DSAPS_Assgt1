#include <iostream>
#include <string>
using namespace std;

template <class T>
class deque
{
private:
    void addSize()
    {
        T *newarr = new T[50 + (2 * this->length) + 50];
        for (int i = 0; i < this->length; i++)
        {
            newarr[50 + i] = *(this->head + i);
        }
        this->arrbegin = newarr;
        this->arrend = newarr + 99 + (2 * this->length);
        this->head = newarr + 50;
        this->tail = newarr + 49 + this->length;
        //delete[] arr;
        this->arr = newarr;
    }

public:
    T *arr;
    T *head;
    T *tail;
    int length;
    T *arrbegin;
    T *arrend;

    deque()
    {
        this->length = 0;
        this->arr = new T[100];
        this->head = this->tail = arr[50];
        this->arrbegin = this->arr;
        this->arrend = this->arr + 99;
    }

    deque(int n, T x)
    {
        this->arr = new T[50 + n + 50];
        this->arrbegin = this->arr;
        this->arrend = (this->arr + 50 + n - 1 + 50);
        for (int i = 0; i < n; i++)
        {
            this->arr[50 + i] = x;
        }
        this->head = this->arr + 50;
        this->tail = this->arr + 50 + n - 1;
        this->length = n;
    }

    void push_back(T x)
    {
        if (this->length == 0)
        {
            *(this->tail) = x;
            this->length++;
            return;
        }
        if (this->tail == this->arrend)
        {
            addSize();
        }
        *(this->tail + 1) = x;
        this->length++;
        this->tail = this->tail + 1;
    }

    void pop_back()
    {
        if (this->length == 0)
        {
            throw out_of_range("Empty deque cannot be popped");
        }
        if (this->length > 1)
            this->tail = this->tail - 1;
        this->length--;
    }

    void push_front(T x)
    {
        if (this->length == 0)
        {
            *(this->head) = x;
            this->length++;
            return;
        }
        if (this->head == this->arrbegin)
        {
            addSize();
        }
        *(this->head - 1) = x;
        this->length++;
        this->head = this->head - 1;
    }

    void pop_front()
    {
        if (this->length == 0)
        {
            throw out_of_range("Empty deque cannot be popped");
        }
        if (this->length > 1)
            this->head = this->head + 1;
        this->length--;
    }

    T front()
    {
        if (this->length == 0)
        {
            throw out_of_range("Cannot show front of empty deque");
        }
        return *(this->head);
    }

    T back()
    {
        if (this->length == 0)
        {
            throw out_of_range("Cannot show back of empty deque");
        }
        return *(this->tail);
    }

    bool empty()
    {
        if (this->length == 0)
            return true;
        return false;
    }

    int size()
    {
        return this->length;
    }

    void resize(int x, T d)
    {
        if (x == 0)
            this->clear();

        else if (this->length == x)
            return;

        else if (this->length == 0)
        {
            T *newarr = new T[50 + x + 50];
            for (int i = 0; i < x; i++)
            {
                newarr[50 + i] = d;
            }
            this->head = newarr + 50;
            this->tail = newarr + x - 1;
            this->arrbegin = newarr;
            this->arrend = newarr + 99 + x;
            this->length = x;
            //delete[] arr;
            this->arr = newarr;
        }

        else if (this->length > x)
        {
            this->tail = this->head + x - 1;
            this->length = x;
        }

        else
        {
            if (x > this->arrend - this->head + 1)
            {
                T *newarr = new T[50 + x + 50];
                for (int i = 0; i < this->length; i++)
                {
                    newarr[50 + i] = *(this->head + i);
                }
                this->head = newarr + 50;
                this->tail = newarr + 49 + this->length;
                this->arrbegin = newarr;
                this->arrend = newarr + 99 + x;
                //delete[] arr;
                this->arr = newarr;
            }

            int diff = x - this->length;
            for (int i = 0; i < diff; i++)
            {
                this->tail = this->tail + 1;
                *(this->tail) = d;
            }
            this->length = x;
        }
    }

    void clear()
    {
        this->tail = this->head;
        this->length = 0;
    }

    T operator[](int n)
    {
        if (this->length == 0)
        {
            throw out_of_range("Deque is empty");
        }
        if (n > this->length - 1)
        {
            throw out_of_range("Your index is not in range of 0 and " + to_string(this->length - 1));
        }
        return *(this->head + n);
    }
};

int main()
{
    deque<int> d(5, 7);
    cout << d[4] << endl;
}