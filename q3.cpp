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
        this->head = this->tail = arr + 50;
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
        if (n > this->length - 1 || n < 0)
        {
            throw out_of_range("Your index is not in range of 0 and " + to_string(this->length - 1));
        }
        return *(this->head + n);
    }

    void display()
    {
        for (int i = 0; i < this->length; i++)
        {
            cout << *(this->head + i) << " ";
        }
        cout << endl;
    }
};

int main()
{
    /*deque<int> d(2, 7);
    for(int i=0;i<75;i++)
    {
        d.push_front(13);
    }
    cout<<d[65]<<endl;
    cout<<d.size()<<endl;*/

    deque<string> *dq = new deque<string>();
    int Q;
    cin >> Q;
    while (Q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            string x;
            cin >> x;
            dq->push_front(x);
            dq->display();
        }
        else if (type == 2)
        {
            dq->pop_front();
            dq->display();
        }
        else if (type == 3)
        {
            string x;
            cin >> x;
            dq->push_back(x);
            dq->display();
        }
        else if (type == 4)
        {
            dq->pop_back();
            dq->display();
        }
        else if (type == 5)
        {
            dq = new deque<string>();
        }
        else if (type == 6)
        {
            int n;
            string x;
            cin >> n;
            cin >> x;
            dq = new deque<string>(n, x);
            dq->display();
        }
        else if (type == 7)
        {
            cout << dq->front() << endl;
        }
        else if (type == 8)
        {
            cout << dq->back() << endl;
        }
        else if (type == 9)
        {
            bool t = dq->empty();
            if (t)
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if (type == 10)
        {
            cout << dq->size() << endl;
        }
        else if (type == 11)
        {
            int x;
            string d;
            cin >> x;
            cin >> d;
            dq->resize(x, d);
            dq->display();
        }
        else if (type == 12)
        {
            dq->clear();
            dq->display();
        }
        else if (type == 13)
        {
            int n;
            cin >> n;
            cout << (*dq)[n] << endl;
        }
        else if (type == 14)
        {
            dq->display();
        }
    }
}