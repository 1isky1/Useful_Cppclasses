# Useful C++ classes
Some useful classes that demonstrate the capabilities of the C++ language. Can be used to solve some arithmetic problems or to simplify writing and improve the readability of code.
## ~Dictionary<TKey,TValue> class~
### Description
The class is a C++ implementation of the C# Dictionary<TKey,TValue> class, and includes some basic methods and properties borrowed from the C# dictionary class.
### Type parameters
**`_Tkey`** - custom key type.

**`_Tvalue`** - custom value type.
### Constructors
| Name | Description |
|:------|:------------|
| dictionary() | Initializes a new instance of the Dictionary<_Tkey,_Tvalue> class that is empty, has the default initial capacity, and uses the default equality comparer for the key type. |
| dictionary(const std::vector<std::pair<_Tkey, _Tvalue>> &_id) | Initializes a new instance of the Dictionary<_Tkey,_Tvalue> class that contains elements copied from the specified std::vector<std::pair<_Tkey, _Tvalue>>. |
### Properties (fields)
| Name | Type | Description |
|:------|:------------|:------------|
| count | size_t | Keeps the number of key-value pairs contained in the Dictionary<_Tkey,_Tvalue>. |
| keys | std::vector<_Tkey> | Returns a collection containing the keys in the Dictionary<_Tkey,_Tvalue>. |
| values | std::vector<_Tvalue> | Returns a collection containing the values in the Dictionary<_Tkey,_Tvalue>. |
### Methods
| Name | Returned type | Description |
|:------|:------------|:------------|
| add(const _Tkey k, const _Tvalue v) | void | Adds the specified key and value to the dictionary. |
| remove(const _Tkey k) | void | Removes the value with the specified key from the Dictionary<_Tkey,_Tvalue> |
| remove(const _Tkey k, _Tvalue &v) | void | Removes the value with the specified key from the Dictionary<_Tkey,_Tvalue> and copies the element to the `v` parameter. |
| contains_key(const _Tkey k) const noexcept | bool | Determines whether the Dictionary<_Tkey,_Tvalue> contains the specified key. |
| contains_val(const _Tvalue v) const noexcept | bool | Determines whether the Dictionary<_Tkey,_Tvalue> contains the specified value. |
| try_add(const _Tkey k, const _Tvalue v) noexcept | bool | Attempts to add the specified key and value to the dictionary. |
| try_get_value(const _Tkey k, _Tvalue &v) const noexcept | bool | Returns the value associated with the specified key. |
| output() | void | Formatted output of Dictionary<_Tkey,_Tvalue>.|

## ~Roman class~
### Description
Class for working with Roman numerals. Includes overloaded unary assignment operator `=` and main binary arithmetic (`+`, `-`) and comparison operators (`>`, `<`, `==`, `>=`, `<=`, `!=`).
### Type parameters
**`std::string`** - main property field type.
### Constructors
| Name | Description |
|:------|:------------|
| roman() | Initializes a new instance of the Roman class that is empty. |
| roman(const int _ui) | Initializes a new instance of the Roman class that initializes main field from int number, and convert to roman string. |
| roman(std::string const& _us) | Initializes a new instance of the Roman class that initializes main field from string. |
### Properties (fields)
| Name | Type | Description |
|:------|:------------|:------------|
| r | std::string | Main field for keeping roman number. |
| romans | dictionary<std::string, int>| Constant dictionary of all main roman literal digits. |