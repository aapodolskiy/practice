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

        // TODO: убрать ведущие нули
        // TODO: сделать со строками
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
                i++;
            }

            current_monom->coefficient = coefficients[i];
            current_monom->power = 0;
            current_monom->next_monom = NULL;
        }

        // декструктор
        // по-хорошему надо пройтись по всему списку и освободить память
        ~Polynomial() {
        }

        // TODO: не выводить первый плюс
        // TODO: сделать +/-
        // TODO: выводить "x" вместо "1x"
        // TODO: не выводить x^0
        // TODO: не выводить моном, если коэффициент равен 0
        void print(char variable = 'x') {
            Monom *current_monom = first_monom;
            do {
                cout
                    << "+"
                    << current_monom->coefficient
                    << variable
                    << "^"
                    << current_monom->power
                ;
                if (current_monom->next_monom != NULL) {
                    current_monom = current_monom->next_monom;
                } else {
                    break;
                }
            } while (true);
        }

        int countValue(const int value) {
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

        // TODO: написать такой же метод,
        //  который бы не менял исходный объект, а возвращал бы новый
        void derivative() {
            Monom *current_monom = first_monom;

            do {
                current_monom->coefficient *= current_monom->power;
                current_monom->power--;
                if (current_monom->power == 0) {
                    delete current_monom->next_monom;
                    current_monom->next_monom = NULL;
                    break;
                } else {
                    current_monom = current_monom->next_monom;
                }
            } while(true);
        }

        int getPower() {
            return first_monom->power;
        }
};

bool isEqual(const Polynomial *p, const Polynomial *q) {
    Monom *current_monom_p = p->first_monom;
    Monom *current_monom_q = q->first_monom;

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

// TODO: убрать ведущие нули
// В этом варианте аргументы функции -- это указатели на объекты
Polynomial Add(Polynomial *p, Polynomial *q) {
    Polynomial result;

    Monom *current_monom_p = p->first_monom;
    Monom *current_monom_q = q->first_monom;

    result.first_monom = new Monom();

    Monom *current_monom_result = result.first_monom;

    for (int current_power = max(p->getPower(), q->getPower()); current_power >= 0; current_power--) {
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

// TODO: убрать ведущие нули
// А в этом варианте аргументы функции -- это ссылки на объекты
// Разница между этими вариантами хорошо описана в первом ответе на вопрос https://ru.stackoverflow.com/questions/484078
// Если коротко, то нам лучше использовать ссылки
// TODO: написать вариант функции isEqual со ссылками вместо указателей (назвать его isEqualByReference)
// Когда разница между ссылками и указателями станет достаточно понятной,
//  можно будет удалить варианты с указателями и оставить только ссылочные варианты
// Тогда эти ссылочные функции можно будет переименовать в просто Add и просто isEqual
Polynomial AddByReference(Polynomial &p, Polynomial &q) {
    Polynomial result;

    Monom *current_monom_p = p.first_monom;
    Monom *current_monom_q = q.first_monom;

    result.first_monom = new Monom();

    Monom *current_monom_result = result.first_monom;

    for (int current_power = max(p.getPower(), q.getPower()); current_power >= 0; current_power--) {
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

int main() {

    // Тестируем конструкторы многочленов
    int coefficients_p[4] = {4, 0, 1, 3};
    int length_p = 4;
    Polynomial p(coefficients_p, length_p);

    int coefficients_q[4] = {5, 2, 1, 3};
    int length_q = 4;
    Polynomial q(coefficients_q, length_q);


    // Тестируем равенство многочленов
    p.print('x');
    cout << endl;
    q.print('y');
    cout << endl;
    if (isEqual(&p, &q) == true) {
        cout << "p == q";
    } else {
        cout << "p != q";
    }
    cout << endl;


    // Тестируем вычисление значений в точке
    p.print('x');
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << "p(" << i << ") = " << p.countValue(i);
        cout << endl;
    }
    cout << endl;


    // Тестируем производную
    cout << endl;
    p.print();
    cout << endl;
    p.derivative();
    p.print();
    cout << endl;


    // Тестируем сложение
    cout << endl;
    p.print();
    cout << endl;
    q.print();
    cout << endl;
    Polynomial r;
    r = AddByReference(p, q);
    r.print();
    cout << endl;


    return 0;
}
