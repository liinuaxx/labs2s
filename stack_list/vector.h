#pragma once
#include <cstddef>
#include "StackImplementation.h"

using ValueType = double;

class Vector : public IStackImplementation {
        private:
		ValueType* _data = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
		float _multiplicativeCoef = 2.0f;
	public:
		Vector() = default;
		Vector(const ValueType* rawArray, const size_t size, float coef = 2.0f);
		explicit Vector(const Vector& other);
		Vector& operator=(const Vector& other);
                ~Vector();

                void push(const ValueType& value) override;
                void pop() override;
                const ValueType& top() const override;
                bool isEmpty() const override;
                size_t size() const override;
};
