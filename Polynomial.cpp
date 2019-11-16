#include <iostream>

// Из стандартного пространства имен std
//  нам понадобятся только операторы ввода-вывода,
//  переход на новую строку
//  и функция взятия максимума
using std::cin;
using std::cout;
using std::endl;
using std::max;

struct Monom {
    int coefficient;
    int power;
    Monom *next_monom;
};

class Polynomial {
public:
    Monom *first_monom;
    
    // конструктор по умолчанию
    Polynomial() {
        first_monom = new Monom();
        first_monom->coefficient = 0;
        first_monom->power = 0;
        first_monom->next_monom = NULL;
    }
    
    // TODO: убрать ведущие нули -- сейчас они убираются на выводе, но лучше бы они не занимали лишнюю память
    // конструктор с переданными значениями
    Polynomial(const int coefficients[], const int length = 1) {
        first_monom = new Monom();
        Monom *current_monom = first_monom;
        
        int i = 0;
        while (i < length - 1) {
            current_monom->coefficient = coefficients[i];
            current_monom->power = length - 1 - i;
            current_monom->next_monom = new Monom();
            current_monom = current_monom->next_monom;
            ++i;
        }
        
        current_monom->coefficient = coefficients[i];
        current_monom->power = 0;
        current_monom->next_monom = NULL;
    }
    
    // декструктор
    // по-хорошему надо пройтись по всему списку и освободить память
    ~Polynomial() {
        // на самом деле деструктор у меня уже написан, просто в другом файле
        // но чтобы его внедрить, нужно ещё написать конструктор копирования
        // (то есть описать, что делать, когда в коде написано p = q, то есть многочлену присваивается другой многочлен)
    }
    
    // функцию print теперь реализуем через перегруженный оператор вывода
    friend std::ostream& operator<< (std::ostream &out, const Polynomial &p) {
        Monom *current_monom = p.first_monom;
        bool is_first_monom = true;
        do {
            if (current_monom->coefficient != 0) {
                if (!is_first_monom) {
                    out << " ";
                }
                
                if (current_monom->coefficient > 0) {
                    if (!is_first_monom) {
                        out << " + ";
                    }
                } else {
                    if (is_first_monom) {
                        out << "- ";
                    } else {
                        out << " - ";
                    }
                }
                
                if (current_monom->coefficient != 1 || current_monom->power == 0) {
                    out << abs(current_monom->coefficient);
                }
                
                if (current_monom->power != 0) {
                    out << "x";
                    if (current_monom->power != 1) {
                        out << "^" << current_monom->power;
                    }
                }
            }
            
            if (current_monom->next_monom != NULL) {
                current_monom = current_monom->next_monom;
            } else {
                break;
            }
            
            is_first_monom = false;
        } while (true);
        
        return out;
    }
    
    // функцию значения в точке реализуем через оператор ()
    int operator() (const int value) {
        Monom *current_monom = first_monom;
        int result = 0;
        while (current_monom->next_monom != NULL) {
            result += current_monom->coefficient;
            result *= value;
            current_monom = current_monom->next_monom;
        }
        result += current_monom->coefficient;
        return result;
    }
    
    // функцию isEqual тоже переделали на оператор
    friend bool operator== (const Polynomial &p, const Polynomial &q) {
        Monom *current_monom_p = p.first_monom;
        Monom *current_monom_q = q.first_monom;
        
        while (current_monom_p->next_monom != NULL && current_monom_q->next_monom != NULL) {
            if ( current_monom_p->power != current_monom_q->power
              || current_monom_p->coefficient != current_monom_q->coefficient
            ) {
                return false;
            }
            
            current_monom_p = current_monom_p->next_monom;
            current_monom_q = current_monom_q->next_monom;
        }
        
        return current_monom_p->power == current_monom_q->power
            && current_monom_p->coefficient == current_monom_q->coefficient
            && current_monom_p->next_monom == NULL
            && current_monom_q->next_monom == NULL
        ;
    }
    
    friend bool operator!= (const Polynomial &p, const Polynomial &q) {
        return !(p == q);
    }
    
    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q) {
        Polynomial result;

        Monom *current_monom_p = p.first_monom;
        Monom *current_monom_q = q.first_monom;

        result.first_monom = new Monom();

        Monom *current_monom_result = result.first_monom;

        for (int current_power = max(p.first_monom->power, q.first_monom->power); current_power >= 0; --current_power) {
            current_monom_result->power = current_power;
            current_monom_result->coefficient = 0;
            
            if (current_power == current_monom_p->power) {
                current_monom_result->coefficient += current_monom_p->coefficient;
                current_monom_p = current_monom_p->next_monom;
            }
            if (current_power == current_monom_q->power) {
                current_monom_result->coefficient += current_monom_q->coefficient;
                current_monom_q = current_monom_q->next_monom;
            }

            if (current_power > 0) {
                current_monom_result->next_monom = new Monom();
                current_monom_result = current_monom_result->next_monom;
            } else {
                current_monom_result->next_monom = NULL;
            }
        }

        return result;
    }
    
    // производная теперь изменяет объект и возвращает его
    Polynomial& differentiate() {
        Monom *current_monom = first_monom;
        
        do {
            current_monom->coefficient *= current_monom->power;
            --current_monom->power;
            if (current_monom->power == 0) {
                delete current_monom->next_monom;
                current_monom->next_monom = NULL;
                break;
            } else {
                current_monom = current_monom->next_monom;
            }
        } while(true);
        
        return *this;
    }
    
    int getPower() {
        return first_monom->power;
    }
};

int main() {
    
    cout << endl
         << "Тестируем конструкторы многочленов" << endl;
    
    // TODO: считывать эти массивы с клавиатуры
    const int coefficients_p[4] = {4, 0, 1, 3};
    const int length_p = 4;
    Polynomial p(coefficients_p, length_p);
    
    const int coefficients_q[4] = {-5, 2, 1, 3};
    const int length_q = 4;
    Polynomial q(coefficients_q, length_q);
    
    cout << "p(x) = " << p << endl
         << "q(x) = " << q << endl
         << endl;
    
    
    cout << endl
         << "Тестируем равенство многочленов" << endl
         << "p(x) = " << p << endl
         << "q(x) = " << q << endl;
    
    if (p == q) {
        cout << "p == q";
    }
    if (p != q) {
        cout << "p != q";
    }
    cout << endl;
    
    
    cout << endl
        << "Тестируем вычисление значений в точке" << endl
        << "p(x) = " << p << endl;
    
    for (int i = 0; i < 10; ++i) {
        cout << "p(" << i << ") = " << p(i) << endl;
    }
    cout << endl;
    
    
    cout << endl << "Тестируем производную" << endl
         << "p(x) = " << p << endl
         << "p'(x) = " << p.differentiate() << endl
         << endl;
    
    
    cout << endl << "Тестируем сложение" << endl
         << "p(x) = " << p << endl
         << "q(x) = " << q << endl
         << "p+q(x) = " << p + q << endl
         << endl;
    
    
    return 0;
}
