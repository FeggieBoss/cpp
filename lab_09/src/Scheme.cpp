#include "Scheme.hpp"

Scheme::Scheme(int capacity) : capacity(capacity)
{
    size = 0;
    figures_ = new Figure *[capacity] { nullptr };
}
Scheme::~Scheme()
{
    for (int i = 0; i < size; ++i)
        delete figures_[i];
    delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg)
{
    figures_[size++] = fg;
}

int Scheme::find_figure(int id)
{
    for (int i = 0; i < size; ++i)
        if (figures_[i]->get_id() == id)
            return i;
    assert(false);
}

void Scheme::remove_figure(int id)
{
    int pos = find_figure(id);
    delete figures_[pos];
    figures_[pos] = nullptr;
    for (int i = pos + 1; i < size; ++i)
        figures_[i - 1] = figures_[i];
    delete figures_[size];
    figures_[--size] = nullptr;
}

void Scheme::print_all_figures()
{
    for (int i = 0; i < size; ++i)
        figures_[i]->print();
}
void Scheme::zoom_figure(int id, int factor)
{
    figures_[find_figure(id)]->zoom(factor);
}
Figure *Scheme::is_inside_figure(int x, int y)
{
    for (int i = 0; i < size; ++i)
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    return nullptr;
}
void Scheme::move(int id, int new_x, int new_y)
{
    figures_[find_figure(id)]->move(new_x, new_y);
}