#include "shared_ptr.hpp"

shared_ptr::Storage::Storage(Matrix *mtx)
{
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage()
{
    delete data_;
    data_ = nullptr;
    ref_count_ = 0;
}

void shared_ptr::Storage::incr()
{
    ++ref_count_;
}
void shared_ptr::Storage::decr()
{
    --ref_count_;
}
int shared_ptr::Storage::getCounter() const
{
    return ref_count_;
}
Matrix *shared_ptr::Storage::getObject() const
{
    return data_;
}

void shared_ptr::change_obj(Matrix *obj) 
{
    if (obj == nullptr)
    {
        storage_ = nullptr;
        return;
    }
    storage_ = new Storage(obj);
}

void shared_ptr::decrement()
{
    if (isNull())
        return;
    storage_->decr();
    if (storage_->getCounter() == 0)
    {
        delete storage_;
        storage_ = nullptr;
    }
}

shared_ptr::shared_ptr(Matrix *obj)
{
    change_obj(obj);
}

shared_ptr::shared_ptr(const shared_ptr &other)
{
    decrement();
    storage_ = other.storage_;
    if (!isNull())
        storage_->incr();
}

shared_ptr &shared_ptr::operator=(shared_ptr other)
{
    std::swap(storage_, other.storage_);
    return *this;
}

shared_ptr::~shared_ptr()
{
    decrement();
}

Matrix *shared_ptr::ptr() const
{
    return operator->();
}

bool shared_ptr::isNull() const
{
    return (storage_ == nullptr);
}

void shared_ptr::reset(Matrix *obj)
{
    decrement();
    change_obj(obj);
}

Matrix *shared_ptr::operator->() const
{
    if (isNull())
        return nullptr;
    return storage_->getObject();
}
Matrix &shared_ptr::operator*() const
{
    return *(storage_->getObject());
}