/*

Solution to the test task on serialization and deserialization using C++17

task:

******************************************************************************************************************************

en:

################################################################################
# Binary Protocol Description
################################################################################

Network packets follow this structure:
packet := size payload

size – The number of elements in the sequence; it can be 0.
payload – A byte stream (blob) consisting of a sequence of serialized variables of different types.

Type Definition and Serialization Order

type := id(uint64_t) data(blob)

data consists of:
	IntegerType – uint64_t
	FloatType – double
	StringType – size(uint64_t) blob
	VectorType – size(uint64_t) ... (serialized variables)

All data is transmitted in little-endian byte order.

You need to implement the following entities: IntegerType, FloatType, StringType, VectorType
Also you need to implement utility entity Any
And craft Serialisator object with a specified interface.

IntegerType, FloatType, and StringType constructors  must initialize similarly to uint64_t, double, and std::string, respectively.
VectorType constructors must allow initialization with a list of any of the mentioned types (IntegerType, FloatType, StringType, VectorType), either by reference or by value.
All specified function signatures must be implemented.
The signatures of template constructors are conditional; in the final implementation, they can be adjusted at the developer's discretion or even removed entirely.
Vector::push must be a template function that accepts any of the types: IntegerType, FloatType, StringType, VectorType.Serialisator::push must be a template function that accepts IntegerType, FloatType, StringType, VectorType, and Any.
All template functions must enforce constraint requirements on template arguments. And usage of static_assert is prohibited.
The main function cannot be modified, except for adding additional checks.

Architectural Requirements:
1. C++17 standard must be used.
2. Virtual functions are prohibited.
3. Multiple and virtual inheritance are prohibited.
4. Heap allocation is prohibited, including the use of smart pointers.
   This does not restrict the use of std::vector, std::string, etc.
5. Code duplication is prohibited, except for strictly justified cases.
   For example, if each XType implementation has its own IdType getId(), it will be considered an error.
6. Value-type fields must not be stored in XType directly – they should be extracted into a generalized entity.
7. No other restrictions apply, including the creation of additional utility entities and helpers.
8. XType must implement serialization and deserialization similar to Any.

Example of VectorType Serialization VectorType(StringType("qwerty"), IntegerType(100500))
{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x71,0x77,0x65,0x72,0x74,0x79,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x94,0x88,
 0x01,0x00,0x00,0x00,0x00,0x00}

******************************************************************************************************************************

ru:

################################################################################
# Описание бинарного протокола
################################################################################

По сети ходят пакеты вида
packet : = size payload

size - размер последовательности, в количестве элементов, может быть 0.

payload - поток байтов(blob)
payload состоит из последовательности сериализованных переменных разных типов :

Описание типов и порядок их сериализации

type : = id(uint64_t) data(blob)

data : =
    IntegerType - uint64_t
    FloatType - double
    StringType - size(uint64_t) blob
    VectorType - size(uint64_t) ...(сериализованные переменные)

Все данные передаются в little endian порядке байтов

Необходимо реализовать сущности IntegerType, FloatType, StringType, VectorType
Кроме того, реализовать вспомогательную сущность Any
Сделать объект Serialisator с указанным интерфейсом.

Конструкторы(ы) типов IntegerType, FloatType и StringType должны обеспечивать инициализацию, аналогичную инициализации типов uint64_t, double и std::string соответственно.
Конструктор(ы) типа VectorType должен позволять инициализировать его списком любых из перечисленных типов(IntegerType, FloatType, StringType, VectorType) переданных как по ссылке, так и по значению.
Все указанные сигнатуры должны быть реализованы.
Сигнатуры шаблонных конструкторов условны, их можно в конечной реализации делать на усмотрение разработчика, можно вообще убрать.
Vector::push должен быть именно шаблонной функцией. Принимает любой из типов: IntegerType, FloatType, StringType, VectorType.
Serialisator::push должен быть именно шаблонной функцией.Принимает любой из типов: IntegerType, FloatType, StringType, VectorType, Any
Реализация всех шаблонных функций, должна обеспечивать constraint requirements on template arguments, при этом, использование static_assert - запрещается.
Код в функции main не подлежит изменению. Можно только добавлять дополнительные проверки.

Архитектурные требования :
1. Стандарт - c++17
2. Запрещаются виртуальные функции.
3. Запрещается множественное и виртуальное наследование.
4. Запрещается создание каких - либо объектов в куче, в том числе с использованием умных указателей.
   Это требование не влечет за собой огранечений на использование std::vector, std::string и тп.
5. Запрещается любое дублирование кода, такие случаи должны быть строго обоснованы. Максимально использовать обобщающие сущности.
   Например, если в каждой из реализаций XType будет свой IdType getId() - это будет считаться ошибкой.
6. Запрещается хранение value_type поля на уровне XType, оно должно быть вынесено в обобщающую сущность.
7. Никаких других ограничений не накладывается, в том числе на создание дополнительных обобщающих сущностей и хелперов.
8. XType должны реализовать сериализацию и десериализацию аналогичную Any.

Пример сериализации VectorType(StringType("qwerty"), IntegerType(100500))
{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x71,0x77,0x65,0x72,0x74,0x79,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x94,0x88,
 0x01,0x00,0x00,0x00,0x00,0x00}

******************************************************************************************************************************

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


*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <string>
#include <variant>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <type_traits>


using Id = uint64_t;
using Buffer = std::vector<std::byte>;

enum class TypeId : Id {
    Uint,
    Float,
    String,
    Vector
};

template<typename T>
class BaseType
{
public:
    using ValueType = T;
    using TypeBaseType = BaseType<T>;

    template<typename ...Args>
    BaseType(Args&& ...args):
			value_ (std::forward<Args>(args)...)
	{}

    bool operator==(const BaseType& other) const
    {
    	return value_ == other.value_;
    }

    const T& getValue() const
    {
    	return value_;
    }

protected:
    T value_;

};

template <	typename T,
			typename = std::enable_if_t<std::is_same_v<T, uint64_t> ||
										std::is_same_v<T, double>   ||
										std::is_same_v<T, TypeId>   >>
void insert_to_buffer (Buffer& _buff, const T value)
{
	_buff.insert(	_buff.end(),
					reinterpret_cast<const std::byte*>(&value),
					reinterpret_cast<const std::byte*>(&value) + sizeof(T));
}

template<	typename T,
			typename = std::enable_if_t<std::is_same_v<T, std::size_t> 	||
										std::is_same_v<T, uint64_t>  	>>
Buffer::const_iterator get_next_begin(Buffer::const_iterator _begin, T offset, Buffer::const_iterator _end)
{
	if (offset > std::distance(_begin, _end))
	{
		throw std::out_of_range("Buffer underflow");
	}
	return std::next(_begin, offset);
}

template<typename T,
typename = std::enable_if_t<std::is_same_v<T, uint64_t> 	||
							std::is_same_v<T, double> 		>>
constexpr std::string_view get_symple_type_name()
{
	return "unknown";
}

template<>
constexpr std::string_view get_symple_type_name<uint64_t>()
{
	return "int";
}

template<>
constexpr std::string_view get_symple_type_name<double>()
{
	return "float";
}


template<typename T>
class SimpleType : public BaseType<T>
{
	static constexpr std::string_view type_name_ = get_symple_type_name<T>();
public:

	using BaseType<T>::BaseType;

	explicit operator std::string() const
	{
		return std::string(type_name_) + " " + std::to_string(BaseType<T>::value_);
	}

    Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end)
	{
    	auto next_begin = get_next_begin(_begin, sizeof(T), _end);
    	std::memcpy(&(this->value_), &(*_begin), sizeof(T));
		return next_begin;
	}

    void serialize(Buffer& _buff) const
	{
    	insert_to_buffer(_buff, BaseType<T>::value_);
	}
};


using IntegerType = SimpleType<uint64_t>;
using FloatType = SimpleType<double>;


class StringType : public BaseType<std::string>
{
public:

	template<typename ...Args>
	StringType(Args&& ...args):
			BaseType (std::forward<Args>(args)...)
	{}

	explicit operator std::string() const
	{
		std::ostringstream oss;
		oss << "string (";
		oss << std::to_string(value_.size());
		oss << "):'";
		for (unsigned char c : value_)
		{
		    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) ;
		}
		oss << "'";
		return  oss.str();
	}

	Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end)
	{
		uint64_t string_size;

		auto next_begin = get_next_begin(_begin, sizeof(uint64_t), _end);

		std::memcpy(&string_size, &(*_begin), sizeof(uint64_t));
		_begin = next_begin;

		next_begin = get_next_begin(_begin, string_size, _end);

		value_ = std::move(std::string(reinterpret_cast<const char*>(&(*_begin)), string_size));

		return next_begin;
	}

	void serialize(Buffer& _buff) const
	{
		insert_to_buffer(_buff, value_.size());
		_buff.insert(	_buff.end(),
						reinterpret_cast<const std::byte*>(value_.data()),
						reinterpret_cast<const std::byte*>(value_.data()) + value_.size());
	}
};


class Any;

class VectorType : public BaseType<std::vector<Any>>
{
public:

	template<typename ...Args>
	VectorType(Args&& ...args):
			BaseType(createVector(std::forward<Args>(args)...))
	{}


    explicit operator std::string() const;

	Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end);

	void serialize(Buffer& _buff) const;

    template <	typename Arg,
				typename = std::enable_if_t<std::is_same_v<std::decay_t<Arg>, IntegerType> 	||
											std::is_same_v<std::decay_t<Arg>, FloatType>   	||
											std::is_same_v<std::decay_t<Arg>, StringType>  	||
											std::is_same_v<std::decay_t<Arg>, VectorType>  	||
											std::is_same_v<std::decay_t<Arg>, Any>   		>>
    void push_back(Arg&& _val)
    {
        value_.emplace_back(std::forward<Arg>(_val));
    }
private:

    std::vector<Any> createVector()
    {
    	return {};
	}

	template<typename Arg, typename... Args>
	std::vector<Any> createVector(Arg&& arg, Args&&... args)
	{
		std::vector<Any> result;
		result.emplace_back(Any(std::forward<Arg>(arg)));
		std::vector<Any> remaining = createVector(std::forward<Args>(args)...);
		result.insert(result.end(), remaining.begin(), remaining.end());
		return result;
	}

};


class Any {

public:

	using VariantType = std::variant<IntegerType, FloatType, StringType, VectorType>;

	template<typename T,
	typename = std::enable_if_t<std::is_same_v<std::decay_t<T>, IntegerType> 	||
								std::is_same_v<std::decay_t<T>, FloatType>   	||
								std::is_same_v<std::decay_t<T>, StringType>  	||
								std::is_same_v<std::decay_t<T>, VectorType>  	>>
	Any(const T& val) :
			value_(val)
	{}

	Any() = default;


	explicit operator std::string() const
	{
		return std::visit(	[](const auto& value)
							{
								return (std::string) value;
							},
							value_);
	}

    void serialize(Buffer& _buff) const
    {
    	insert_to_buffer(_buff, getPayloadTypeId());
        std::visit(	[&_buff](const auto& value)
        			{
        				value.serialize(_buff);
        			},
					value_);
    }

    Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end)
    {
    	uint64_t raw_any_type;

    	auto next_begin = get_next_begin(_begin, sizeof(uint64_t), _end);

		std::memcpy(&raw_any_type, &(*_begin), sizeof(uint64_t));
		_begin = next_begin;

		TypeId any_type = static_cast<TypeId>(raw_any_type);

		switch (any_type)
		{
		case TypeId::Uint: 		value_ = IntegerType{};
								break;
		case TypeId::Float:		value_ = FloatType{};
								break;
		case TypeId::String:	value_ = StringType{};
								break;
		case TypeId::Vector:	value_ = VectorType{};
								break;
		default:				throw(std::range_error("wrong TypeID " + std::to_string(raw_any_type)));
		}

		std::visit(	[&_begin, &_end](auto& val)
					{
						_begin = val.deserialize(_begin, _end);
					},
					value_);

		return _begin;
	}

    TypeId getPayloadTypeId() const
    {
		return static_cast<TypeId>(value_.index());
	}

    template<	typename Type,
				typename = std::enable_if_t<std::is_same_v<Type, IntegerType> 	||
											std::is_same_v<Type, FloatType>   	||
											std::is_same_v<Type, StringType>  	||
											std::is_same_v<Type, VectorType>  	>>
    auto& getValue() const
    {
    	return std::get<Type>(value_);
    }

    template<TypeId kId>
    auto& getValue() const {
        return std::get<static_cast<std::size_t>(kId)>(value_);
    }

    bool operator == (const Any& _o) const
    {
        return value_ == _o.value_;
    }

private:
    VariantType value_;
};

VectorType::operator std::string() const
{
	std::ostringstream oss;
	oss << "vector (";
	oss << std::to_string(TypeBaseType::value_.size());
	oss << "): [";
	if (!TypeBaseType::value_.empty()) {
		oss << (std::string)(TypeBaseType::value_[0]);
		for (std::size_t index = 1; index < TypeBaseType::value_.size(); ++index) {
			oss << ", " << (std::string)(TypeBaseType::value_[index]);
		}
	}
	oss << "]";
	return oss.str();
}


Buffer::const_iterator VectorType::deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end)
{
	uint64_t vector_size;

	auto next_begin = get_next_begin(_begin, sizeof(uint64_t), _end);

	std::memcpy(&vector_size, &(*_begin), sizeof(uint64_t));
	_begin = next_begin;

	value_.clear();
	value_.reserve(vector_size);

	for(uint64_t index = 0; index < vector_size; ++index)
	{
		Any element;
		_begin = element.deserialize(_begin, _end);
		push_back(element);
	}

	return _begin;
}

void VectorType::serialize(Buffer& _buff) const
{
	insert_to_buffer(_buff, value_.size());
	for (const auto & element : value_)
	{
		element.serialize(_buff);
	}
}


class Serializator {
public:
    template<	typename Arg,
				typename = std::enable_if_t<std::is_same_v<std::decay_t<Arg>, IntegerType> 	||
											std::is_same_v<std::decay_t<Arg>, FloatType>   	||
											std::is_same_v<std::decay_t<Arg>, StringType>  	||
											std::is_same_v<std::decay_t<Arg>, VectorType>  	||
											std::is_same_v<std::decay_t<Arg>, Any>  		>>
    void push(Arg&& _val)
    {
        storage_.emplace_back(std::forward<Arg>(_val));
    }

    Buffer serialize() const
    {
		Buffer res;

		insert_to_buffer(res, storage_.size());

		for (const auto& item : storage_)
		{
			item.serialize(res);
		}
		return res;
	}

    static std::vector<Any> deserialize(const Buffer& _val)
    {
		std::vector<Any> res;

		auto it = _val.begin();
		auto end = _val.end();

		IntegerType elem_count;

		it = elem_count.deserialize(it, end);

		auto elem_count_uint = elem_count.getValue();

		res.reserve(elem_count_uint);

		for(uint64_t index = 0; index < elem_count_uint; ++index)
		{
			Any element;
			it = element.deserialize(it, end);
			res.push_back(element);
		}

		return res;
    }

    const std::vector<Any>& getStorage() const
    {
		return storage_;
	}

private:
    std::vector<Any> storage_;
};

void print_vector (const std::vector<Any>& to_ptint)
{
	std::cout << to_ptint.size() << std::endl;
	for (const auto & elem : to_ptint)
	{
		std::cout << static_cast<std::string>(elem) << std::endl;
	}
}

void checks(void)
{
	VectorType v_1;
	IntegerType i_1 = 5;
	IntegerType i_2 = {6};
	int ii = 9;
	IntegerType i_3 = ii;
	FloatType f_1 = 1.1;
	FloatType f_2 = 3;
	StringType s_1 = "asdfsaf";
	VectorType v_2 = {i_1, f_1, s_1};
	VectorType v_3 = {i_2, i_3, f_2, v_2};
	VectorType v_4 = std::move(v_3);
	VectorType v_5(StringType("qwerty"), IntegerType(100500));
	v_1.push_back(v_2);
	v_1.push_back(std::move(f_1));
	const FloatType& f_2_r = f_2;
	v_1.push_back(f_2_r);

	Any a_1;
	Any a_2 (i_1);
	Any a_3 (f_2_r);
	Any a_4 (std::move(s_1));
	Any a_5 (v_1);

	std::cout << static_cast<std::string>( a_1.getValue<IntegerType>() ) << std::endl;
	std::cout << static_cast<std::string>( a_2.getValue<IntegerType>() ) << std::endl;
	std::cout << static_cast<std::string>( a_3.getValue<FloatType>() ) << std::endl;
	std::cout << static_cast<std::string>( a_4.getValue<StringType>() ) << std::endl;
	std::cout << static_cast<std::string>( a_5.getValue<VectorType>() ) << std::endl;
	std::cout << static_cast<std::string>( a_1.getValue<TypeId::Uint>() ) << std::endl;
	std::cout << static_cast<std::string>( a_2.getValue<TypeId::Uint>() ) << std::endl;
	std::cout << static_cast<std::string>( a_3.getValue<TypeId::Float>() ) << std::endl;
	std::cout << static_cast<std::string>( a_4.getValue<TypeId::String>() ) << std::endl;
	std::cout << static_cast<std::string>( a_5.getValue<TypeId::Vector>() ) << std::endl;

	std::cout << "------------------" << std::endl;

	Serializator s;
	s.push(v_2);
	s.push(i_1);
	s.push(f_2_r);
	s.push(std::move(s_1));
	s.push(Any(v_3));
	s.push(v_4);
	s.push(v_1);
	s.push(v_5);
	print_vector(s.getStorage());

	std::cout << "------------------" << std::endl;
}

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

    //print_vector(res);

    //checks();

    Serializator s;
    for (auto&& i : res)
        s.push(i);

    std::cout << (buff == s.serialize()) << '\n';

    return 0;
}
