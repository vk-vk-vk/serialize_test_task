# Solution to the Test Task on Serialization and Deserialization using C++17

## Task Description

---

### English Version

#### Binary Protocol Description

Network packets follow this structure:

```
packet := size payload
```

- **size** – The number of elements in the sequence; it can be 0.
- **payload** – A byte stream (blob) consisting of a sequence of serialized variables of different types.

#### Type Definition and Serialization Order

```
type := id(uint64_t) data(blob)
```

**Data consists of:**
- `IntegerType` – `uint64_t`
- `FloatType` – `double`
- `StringType` – `size(uint64_t) blob`
- `VectorType` – `size(uint64_t) ... (serialized variables)`

All data is transmitted in little-endian byte order.

#### Requirements

- You need to implement the following entities: `IntegerType`, `FloatType`, `StringType`, `VectorType`
- Also you need to implement utility entity `Any`
- And craft `Serialisator` object with a specified interface.

**Implementation Details:**

- `IntegerType`, `FloatType`, and `StringType` constructors  must initialize similarly to `uint64_t`, `double`, and `std::string`, respectively.
- `VectorType` constructors must allow initialization with a list of any of the mentioned types (`IntegerType`, `FloatType`, `StringType`, `VectorType`), either by reference or by value.
- All specified function signatures must be implemented.
- The signatures of template constructors are conditional; in the final implementation, they can be adjusted at the developer's discretion or even removed entirely.
- `Vector::push` must be a template function that accepts any of the types: `IntegerType`, `FloatType`, `StringType`, `VectorType`.
- `Serialisator::push` must be a template function that accepts `IntegerType`, `FloatType`, `StringType`, `VectorType`, and `Any`.
- All template functions must enforce constraint requirements on template arguments. And usage of `static_assert` is prohibited.
- The `main` function cannot be modified, except for adding additional checks.

#### Architectural Requirements:

1. C++17 standard must be used.
2. Virtual functions are prohibited.
3. Multiple and virtual inheritance are prohibited.
4. Heap allocation is prohibited, including smart pointers. This does not restrict the use of `std::vector`, `std::string`, etc.
5. Code duplication is prohibited, except for strictly justified cases. For example, if each `XType` implementation has its own `IdType getId()`, it will be considered an error.
6. `Value-type` fields must not be stored directly in `XType` – they should be extracted into a generalized entity.
7. No other restrictions apply, including the creation of additional utility entities and helpers.
8. `XType` must implement serialization and deserialization similar to `Any`.


#### Example of VectorType
 
Serialization `VectorType(StringType("qwerty"), IntegerType(100500))`

```
{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x71,0x77,0x65,0x72,0x74,0x79,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x94,0x88,
 0x01,0x00,0x00,0x00,0x00,0x00}
```

---

### Russian Version

#### Описание бинарного протокола

По сети ходят пакеты вида

```
packet : = size payload
```

- **size** – Размер последовательности (количество элементов), может быть `0`.
- **payload** – Поток байтов (blob), состоящий из последовательности сериализованных переменных разных типов.

#### Описание типов и порядок сериализации

```
type := id(uint64_t) data(blob)
```

**Data состоит из:**
- `IntegerType` – `uint64_t`
- `FloatType` – `double`
- `StringType` – `size(uint64_t) blob`
- `VectorType` – `size(uint64_t) ... (сериализованные переменные)`

Все данные передаются в little endian порядке байтов

#### Требования

- Необходимо реализовать сущности `IntegerType`, `FloatType`, `StringType`, `VectorType`
- Кроме того, реализовать вспомогательную сущность `Any`
- Сделать объект `Serialisator` с указанным интерфейсом.

**Детали реализаии:**

- Конструкторы(ы) типов `IntegerType`, `FloatType` и `StringType` должны обеспечивать инициализацию, аналогичную инициализации типов `uint64_t`, `double` и `std::string` соответственно.
- Конструктор(ы) типа `VectorType` должен позволять инициализировать его списком любых из перечисленных типов(`IntegerType`, `FloatType`, `StringType`, `VectorType`) переданных как по ссылке, так и по значению.
- Все указанные сигнатуры должны быть реализованы.
- Сигнатуры шаблонных конструкторов условны, их можно в конечной реализации делать на усмотрение разработчика, можно вообще убрать.
- `Vector::push` должен быть именно шаблонной функцией. Принимает любой из типов: `IntegerType`, `FloatType`, `StringType`, `VectorType`.
- `Serialisator::push` должен быть именно шаблонной функцией.Принимает любой из типов: `IntegerType`, `FloatType`, `StringType`, `VectorType`, `Any`
- Реализация всех шаблонных функций, должна обеспечивать constraint requirements on template arguments, при этом, использование `static_assert` - запрещается.
- Код в функции `main` не подлежит изменению. Можно только добавлять дополнительные проверки.

#### Архитектурные требования :

1. Стандарт - c++17
2. Запрещаются виртуальные функции.
3. Запрещается множественное и виртуальное наследование.
4. Запрещается создание каких - либо объектов в куче, в том числе с использованием умных указателей.
   Это требование не влечет за собой огранечений на использование `std::vector`, `std::string` и тп.
5. Запрещается любое дублирование кода, такие случаи должны быть строго обоснованы. Максимально использовать обобщающие сущности.
   Например, если в каждой из реализаций `XType` будет свой `IdType getId()` - это будет считаться ошибкой.
6. Запрещается хранение `value_type` поля на уровне `XType`, оно должно быть вынесено в обобщающую сущность.
7. Никаких других ограничений не накладывается, в том числе на создание дополнительных обобщающих сущностей и хелперов.
8. `XType` должны реализовать сериализацию и десериализацию аналогичную `Any`.

#### Пример сериализации 

`VectorType(StringType("qwerty"), IntegerType(100500))`

```
{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x71,0x77,0x65,0x72,0x74,0x79,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x94,0x88,
 0x01,0x00,0x00,0x00,0x00,0x00}
```
---

```
#include <iostream>
#include <vector>
#include <fstream>

using Id = uint64_t;
using Buffer = std::vector<std::byte>;

enum class TypeId : Id {
    Uint,
    Float,
    String,
    Vector
};

class IntegerType {
public:
    template<typename ...Args>
    IntegerType(Args&& ...);
};

class FloatType {
public:
    template<typename ...Args>
    FloatType(Args&& ...);
};

class StringType {
public:
    template<typename ...Args>
    StringType(Args&& ...);
};

class VectorType {
public:
    template<typename ...Args>
    VectorType(Args&& ...);

    template<typename Arg>
    void push_back(Arg&& _val);
};

class Any {
public:
    template<typename ...Args>
    Any(Args&& ...);

    void serialize(Buffer& _buff) const;

    Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end);

    TypeId getPayloadTypeId() const;

    template<typename Type>
    auto& getValue() const;

    template<TypeId kId>
    auto& getValue() const;

    bool operator == (const Any& _o) const;
};

class Serializator {
public:
    template<typename Arg>
    void push(Arg&& _val);

    Buffer serialize() const;

    static std::vector<Any> deserialize(const Buffer& _val);

    const std::vector<Any>& getStorage() const;
};


int main() {

    std::ifstream raw;
    raw.open("raw.bin", std::ios_base::in | std::ios_base::binary);
    if (!raw.is_open())
        return 1;
    raw.seekg(0, std::ios_base::end);
    std::streamsize size = raw.tellg();
    raw.seekg(0, std::ios_base::beg);

    Buffer buff(size);
    raw.read(reinterpret_cast<char*>(buff.data()), size);

    auto res = Serializator::deserialize(buff);

    Serializator s;
    for (auto&& i : res)
        s.push(i);

    std::cout << (buff == s.serialize()) << '\n';

    return 0;
} 
```
 