#include <iostream>
#include <math.h>
#include <stdio.h>


//using namespace std;

struct Spis1 {
    int  info;
    Spis1* prev, * next;
};

Spis1* begin = nullptr, * end = nullptr, * t, * b, * e;

void Create_Spis1(Spis1**, Spis1**, int);
void Add_Spis1(int, Spis1**, Spis1**, int);
void View_Spis1(int, Spis1*);

//------------------- Создание первого элемента --------------------------------------------
void Create_Spis1(Spis1** b, Spis1** e, int in) {
    t = new Spis1;
    t->info = in;
    t->next = t->prev = NULL;
    *b = *e = t;
}
//------------------- Добавление элемента в список ----------------------------------------
void Add_Spis1(int kod, Spis1** b, Spis1** e, int in) {
    t = new Spis1;
    t->info = in;
    if (kod == 0) {
        t->prev = NULL;
        t->next = *b;
        (*b)->prev = t;
        *b = t;
    }
    else {
        t->next = NULL;
        t->prev = *e;
        (*e)->next = t;
        *e = t;
    }
}
void View_Spis1(int kod, Spis1* t) {
    while (t != NULL) {
        std::cout << t->info << std::endl;
        if (kod == 0) t = t->next;
        else t = t->prev;
    }
}


void Del_All(Spis1** _b, Spis1** _e)
{
#ifdef _MSC_VER
    _ASSERTE((_b != nullptr) && (_e != nullptr));
#endif
    Spis1 *_cur = *_b;
    Spis1 *_del;
    while (_cur != nullptr)
    {
        _del = _cur;
        _cur = _cur->next;
        delete _del;
    }
    *_b = *_e = nullptr;
}

/// Удалить из двух связного списка чётные или нечётные значения
/// Параметры:
///   Spis1 **_b - указатель на указатель на начало списка
///   Spis1 **_e - указатель на указатель на конец списка
///   bEvenOdd   - если == true, то удалить чётные, иначе - нечётные
void Dell_Even_Odd(Spis1 **_b, Spis1** _e, bool bEvenOdd)
{
#ifdef _MSC_VER
    _ASSERTE((_b != nullptr) && (_e != nullptr));
#endif

    Spis1 *_cur = *_b;
    Spis1 *_del;
    while (_cur != nullptr)
    {
        // проверка на удаление
        if (bEvenOdd ? (_cur->info % 2) == 0 : (_cur->info % 2) != 0)
        {
            _del = _cur;
            // если первый элемент
            if (_cur->prev == nullptr)
            {
                // передвинуть указатель на следующий элемент и скорректировать указатель на начало списка
                *_b = _cur = _cur->next;
                // проверка на единственный элемент в списке
                if (_cur != nullptr)
                    _cur->prev = nullptr;
                else
                    *_e = _cur;
            }
            else
            {
                // если последний элемент
                if (_cur->next == nullptr)
                {
                    // скорректировать указатель на последний элемент
                    *_e = _cur->prev;
                    // скорректировать указатель на следующий элемент предпоследнего элемента
                    _cur->prev->next = nullptr;
                    // обнулить текущий, т.к. следующего нет
                    _cur = nullptr;
                }
                else
                {
                    // обычный элемент списка в середине

                    // предыдущий должен указать на следующий после текущего
                    _cur->prev->next = _cur->next;
                    // следующий должен указать на предыдущий перед текущим
                    _cur->next->prev = _cur->prev;
                    // переход текущего на следующий
                    _cur = _cur->next;
                }
            }
            // удалить
            delete _del;
        }
        else
        {
            // если не удаление, то переход на следующий элемент
            _cur = _cur->next;
        }
    }
}

int main()
{
    // установка русской локали
    setlocale(LC_ALL, "Rus");

    int in, kod, kod1;
    char Str[2][10] = { "Begin ", "End " };
    while (true) {
        std::cout << "\n\tCreat - 1\n\tAdd - 2\n\tView - 3\n\tУдалить всё - 4\n\tУдалить чёт/нечёт - 5\n\tEXIT - 0 : ";
        std::cin >> kod;
        switch (kod) {

        case 1:/* if (begin != NULL) {
            std::cout << "Clear Memory!" << std::endl;
            break;
        }*/ // то что сверху - плохой тон: - два break в одном case; - не форматировано
            if (begin != NULL)
            {
                std::cout << "Очистите список перед созданием!" << std::endl;
            }
            else
            {
                std::cout << "Begin Info = ";
                std::cin >> in;
                Create_Spis1(&begin, &end, in);
                std::cout << "Creat Begin = " << begin->info << std::endl;
            }
            break;
        case 2:
            if (begin != nullptr)
            {
                std::cout << "Info = ";
                std::cin >> in;
                std::cout << "Add Begin - 0, Add End - 1 : ";
                std::cin >> kod1;
                Add_Spis1(kod1, &begin, &end, in);
                if (kod1 == 0) t = begin;
                else t = end;
                std::cout << "Add to " << Str[kod1] << "" << t->info << std::endl;
            }
            else
            {
                std::cout << "Список пустой! Некуда добавлять!" << std::endl;
            }
            break;

        case 3:/* if (!begin) {
            std::cout << "Stack Pyst!" << std::endl;
            break;
        }*/ // то что сверху - плохой тон: - два break в одном case; - не форматировано
            if (begin == NULL)
            {
                std::cout << "Список пуст!" << std::endl;
            }
            else
            {
                std::cout << "View Begin-0,View End-1:";
                std::cin >> kod1;
                if (kod1 == 0) {
                    t = begin;
                    std::cout << "-- Begin --" << std::endl;
                }
                else {
                    t = end;
                    std::cout << "--- End --" << std::endl;
                }
                View_Spis1(kod1, t);
            }
            break;
        case 4:
            Del_All(&begin, &end);
            std::cout << "Memory Free!" << std::endl;
            break;
        case 5:
            if (begin != nullptr)
            {
                do
                {
                    std::cout << "Удалить чётные - 0, Удалить нечётные - 1, Отмена - 3 : ";
                    std::cin >> kod1;
                }while ((kod1 < 0) || (kod1 > 3));
                if ((kod1 == 0) || (kod1 == 1))
                {
                    Dell_Even_Odd(&begin, &end, kod1 == 0);
                    View_Spis1(0, begin);
                }
            }
            else
            {
                std::cout << "Список пустой!" << std::endl;
            }
            break;
        case 0:
            if (begin != NULL)
                Del_All(&begin, &end);
            return 0;
        }
    }
}
