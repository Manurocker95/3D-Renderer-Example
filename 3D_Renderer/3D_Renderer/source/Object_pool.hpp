#include <cstdint>

namespace ManuelRodriguezMatesanz
{
	template< size_t SIZE >
	class Memory_Pool
	{

		uint8_t buffer[SIZE];
		size_t  allocated;

	public:

		Memory_Pool()
		{
			allocated = 0;
		}

		void * allocate(size_t byte_count)
		{
			if (allocated + byte_count < SIZE)
			{
				void * block = buffer + allocated;

				allocated += byte_count;

				return block;
			}

			return nullptr;
		}

		void * get_start()
		{
			return buffer;
		}

	};

	template< typename TYPE, size_t SIZE >
	class Object_Pool
	{

		Memory_Pool< SIZE * sizeof(TYPE) > memory_pool;

		size_t count;

	public:


		Object_Pool()
		{
			count = 0;
		}

		~Object_Pool()
		{
			TYPE * it = reinterpret_cast<TYPE *>(memory_pool.get_start());

			while (count--)
			{
				(it++)->~TYPE();
			}
		}


		TYPE * allocate()
		{
			TYPE * object = reinterpret_cast<TYPE *>(memory_pool.allocate(sizeof(TYPE)));

			if (object)
			{
				new TYPE(object) ();
			}

			return object;
		}


	};
}