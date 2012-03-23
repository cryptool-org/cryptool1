//////////////////////////////////////////////////////////////////////////////////
// Name:      actBlob.h
// Product:   cv act library
// Purpose:   class Blob written for Visual C++ 6.0, CodeWarrior 4.0,
//            Borland C++ Builder 4
//            The datatype Blob (Binary Large Object) is a universal type, which
//            can be used for any data. The class Blob almost behaves like 
//            std::vector<unsigned char> with the difference that freed memory 
//            is filled with zeros to enhance security.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_BLOB_H
#define ACT_BLOB_H

#include "actBasics.h"
#include "actException.h"

#ifndef UNDER_CE_30
#	include <iostream>
#endif // UNDER_CE_30

#ifndef NO_STL_SUPPORT
#	include <utility>	// used for reserve_iterator
#	include <string>	// used for string
#else
	// --------------------------------------------------------------------------------
	// if there is no STL support, we define reverse_iterator here.
	// --------------------------------------------------------------------------------
	namespace std
	{	
				// ITERATOR TAGS (from <iterator>)
		struct input_iterator_tag {};
		struct output_iterator_tag {};
		struct forward_iterator_tag
			: public input_iterator_tag {};
		struct bidirectional_iterator_tag
			: public forward_iterator_tag {};
		struct random_access_iterator_tag
			: public bidirectional_iterator_tag  {};

		// TEMPLATE CLASS iterator (from <iterator>)
		template<class _C, class _Ty, class _D = ptrdiff_t>
			struct iterator {
			typedef _C iterator_category;
			typedef _Ty value_type;
			typedef _D distance_type;
			};
		template<class _Ty, class _D>
			struct _Bidit : public iterator<bidirectional_iterator_tag,
				_Ty, _D> {};
		template<class _Ty, class _D>
			struct _Ranit : public iterator<random_access_iterator_tag,
				_Ty, _D> {};
		
		// TEMPLATE CLASS iterator_traits (from <iterator>)
		template<class _It>
			struct iterator_traits {
			typedef _It::iterator_category iterator_category;
			typedef _It::value_type value_type;
			typedef _It::distance_type distance_type;
			};

		
		// TEMPLATE CLASS reverse_iterator (from <iterator>)
		template<class _RI,
			class _Ty,
			class _Rt = _Ty&,
			class _Pt = _Ty *,
			class _D = int>
			class reverse_iterator : public _Ranit<_Ty, _D> {
		public:
			typedef reverse_iterator<_RI, _Ty, _Rt, _Pt, _D> _Myt;
			typedef _RI iter_type;
			typedef _Rt reference_type;
			typedef _Pt pointer_type;
			reverse_iterator()
				{}
			explicit reverse_iterator(_RI _X)
				: current(_X) {}
			_RI base() const
				{return(current); }
			_Rt operator*() const
				{return(*(current - 1)); }
		//	_Pt operator->() const
		//		{return(&**this); }
			_Myt& operator++()
				{--current;
				return(*this); }
			_Myt operator++(int)
				{_Myt _Tmp = *this;
				--current;
				return(_Tmp); }
			_Myt& operator--()
				{++current;
				return(*this); }
			_Myt operator--(int)
				{_Myt _Tmp = *this;
				++current;
				return(_Tmp); }
			_Myt& operator+=(_D _N)
				{current -= _N;
				return(*this); }
			_Myt operator+(_D _N) const
				{return(_Myt(current - _N)); }
			_Myt& operator-=(_D _N)
				{current += _N;
				return(*this); }
			_Myt operator-(_D _N) const
				{return(_Myt(current + _N)); }
			_Rt operator[](_D _N) const
				{return(*(*this + _N)); }
		protected:
			_RI current;
			};
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator==(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_X) == get_base(_Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator!=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_X == _Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator<(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_Y) < get_base(_X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator>(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(_Y < _X); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator<=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_Y < _X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator>=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_X < _Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			_D __cdecl operator-(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_Y) - get_base(_X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			reverse_iterator<_RI, _Ty, _Rt, _Pt, _D> __cdecl operator+(_D _N,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>(
				get_base(_Y) - _N)); }
	}	// namespace std

#endif //NO_STL_SUPPORT



// --------------------------------------------------------------------------------
namespace act
{	
#if(_MSC_VER >= 1300)
	template
	<
		class _Ty,
		class _Diff,
		class _Pointer,
		class _Reference,
		class _Pointer2,
		class _Reference2
	>
	class _Ptrit : 
		public std::iterator<std::random_access_iterator_tag, _Ty, _Diff, _Pointer, _Reference>
	{	// wrap pointer as random-access iterator
	public:
		typedef _Ptrit<_Ty, _Diff, _Pointer, _Reference, _Pointer2, _Reference2> _Myt;

		_Ptrit()
		{	// construct with uninitialized wrapped pointer
		}

		_Ptrit(_Pointer _Ptr) : current(_Ptr)
		{	// construct wrapped pointer from _Ptr
		}

		_Ptrit(const _Ptrit<_Ty, _Diff, _Pointer2, _Reference2, _Pointer2, _Reference2>& _Iter)
			: current(_Iter.base())
		{	// const converter or copy constructor
		}

		_Pointer base() const
		{	// return wrapped pointer
			return(current);
		}

		_Reference operator*() const
		{	// return designated value
			return(*current);
		}

		_Pointer operator->() const
		{	// return pointer to class object
			return(&**this);
		}

		_Myt& operator++()
		{	// preincrement
			++current;
			return(*this);
		}

		_Myt operator++(int)
		{	// postincrement
			_Myt _Tmp = *this;
			++current;
			return(_Tmp);
		}

		_Myt& operator--()
		{	// predecrement
			--current;
			return(*this);
		}

		_Myt operator--(int)
		{	// postdecrement
			_Myt _Tmp = *this;
			--current;
			return(_Tmp);
		}

		bool operator==(size_t _Right) const
		{	// test if wrapped pointer == integer (null pointer constant)
			return(current == (_Pointer)_Right);
		}

		bool operator==(const _Myt& _Right) const
		{	// test for iterator equality
			return(current == _Right.current);
		}

		bool operator!=(const _Myt& _Right) const
		{	// test for iterator inequality
			return(!(*this == _Right));
		}

		_Myt& operator+=(_Diff _Off)
		{	// increment by integer
			current += _Off;
			return(*this);
		}

		_Myt operator+(_Diff _Off) const
		{	// return this + integer
			return(_Myt(current + _Off));
		}

		_Myt& operator-=(_Diff _Off)
		{	// decrement by integer
			current -= _Off;
			return(*this);
		}

		_Myt operator-(_Diff _Off) const
		{	// return this - integer
			return(_Myt(current - _Off));
		}

		_Reference operator[](_Diff _Off) const
		{	// subscript
			return(*(*this + _Off));
		}

		bool operator<(const _Myt& _Right) const
		{	// test if this < _Right
			return(current < _Right.current);
		}

		bool operator>(const _Myt& _Right) const
		{	// test if this > _Right
			return(_Right < *this);
		}

		bool operator<=(const _Myt& _Right) const
		{	// test if this <= _Right
			return(!(_Right < *this));
		}

		bool operator>=(const _Myt& _Right) const
		{	// test if this >= _Right
			return(!(*this < _Right));
		}

		_Diff operator-(const _Myt& _Right) const
		{	// return difference of iterators
			return(current - _Right.current);
		}

	protected:
		_Pointer current;	// the wrapped pointer
	};

#endif // _MSC_VER >= 1300

	class Blob
	{
		public:		
			typedef unsigned char	byte;
			typedef byte&			reference;
			typedef const byte&		const_reference;
			typedef size_t			size_type;
			typedef ptrdiff_t		difference_type;
			typedef byte			value_type;
			typedef byte*			pointer;
			typedef const byte*		const_pointer;

			#if(_MSC_VER >= 1300)
				typedef _Ptrit
				<	value_type, difference_type, pointer, reference, pointer, reference
				>	iterator;

				typedef _Ptrit
				<	value_type, difference_type, const_pointer, const_reference, pointer, reference
				>	const_iterator;

				inline static pointer get_base(iterator it)
				{
					return(it.base());
				}

				inline static const_pointer get_base(const_iterator it)
				{
					return(it.base());
				}

			#else
				typedef byte*		iterator;
				typedef const byte*	const_iterator;

				inline static pointer get_base(iterator it)
				{
					return(it);
				}

				inline static const_pointer get_base(const_iterator it)
				{
					return(it);
				}

			#endif

			
			#if (_MSC_VER >= 1200) && (_MSC_VER < 1300)
				typedef std::reverse_iterator
				<	iterator, value_type, reference, pointer, difference_type
				>	reverse_iterator;

				typedef std::reverse_iterator
				<	const_iterator, value_type, const_reference, const_pointer, difference_type
				>	const_reverse_iterator;

			#else
				typedef std::reverse_iterator<iterator>	reverse_iterator;
				typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			#endif			
			
			// construct/copy/destroy
			explicit Blob(const char* str);
#ifndef NO_STL_SUPPORT
			explicit Blob(std::string& str);
#endif // NO_STL_SUPPORT

			Blob();

			Blob(size_type n, byte v = byte(0));
			Blob(const Blob& x);
			
			template<class inputit> Blob(inputit f, inputit l)
				: mFirst(0), mLast(0), mEnd(0)
			{
				insert(begin(), f, l); 				
			}

			~Blob();
			Blob&					operator=(const Blob& x);

			//void					assign(const_iterator f, const_iterator l);
			template<class inputit> void assign(inputit f, inputit l)
			{
				erase(begin(), end());
				insert(begin(), f, l); 
			}


			void					assign(size_type n, byte x = byte(0));

			// iterators
			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

			// capacity
			size_type				size() const;
			size_type				max_size() const;
			void					resize(size_type n, byte x = byte(0));
			size_type				capacity() const;
			bool					empty() const;
			void					reserve(size_type n);

			// element access:
			const_reference			operator[](size_type p) const;
			reference				operator[](size_type p);
			const_reference			at(size_type p) const;
			reference				at(size_type p);
			reference				front();
			const_reference			front() const;
			reference				back();
			const_reference			back() const;

			// modifiers
			void					push_back(byte x);
			void					pop_back();
			iterator				insert(iterator p, byte x = byte(0));
			void					insert(iterator p, size_type m, byte x);

			//void					insert(iterator p, const_iterator f, const_iterator l);
			template<class inputit> void insert(iterator p, inputit f, inputit l)
			{
				size_type m = 0;
				_distance(f, l, m);
				if(size_type(mEnd - mLast) < m) 
				{
					size_type n = size() + (m < size() ? size() : m);
					iterator s = allocate(n, (void *)0);
					iterator q = ucopy(mFirst, p, s);
					q = ucopy(f, l, q);
					ucopy(p, mLast, q);
					_destroy(mFirst, mLast);
					deallocate(get_base(mFirst), mEnd - mFirst);
					mEnd = s + n;
					mLast = s + size() + m;
					mFirst = s; 
				}
				else if(size_type(mLast - p) < m) 
				{
					ucopy(p, mLast, p + m);
					ucopy(f + (mLast - p), l, mLast);
					copy(f, f + (mLast - p), p);
					mLast += m; 
				}
				else if(0 < m) 
				{
					ucopy(mLast - m, mLast, mLast);
					copy_backward(p, mLast - m, mLast);
					copy(f, l, p);
					mLast += m; 
				}
			}

			void					append(const Blob& x);
			void					append(size_type m, byte x);
			template<class inputit> void append(inputit f, inputit l)
			{
				insert(end(), f, l); 
			}

			iterator				erase(iterator p);
			iterator				erase(iterator f, iterator l);
			void					clear();
			void					swap(Blob& x);

			// used by compare operators
			bool					_eq(const Blob& x) const;
			bool					_lt(const Blob& x) const; 
		private:

			template<typename inputit,typename outputit> outputit copy(inputit f, inputit l, outputit x)
			{
				for(; f != l; ++x, ++f)
					*x = *f;
				return(x); 
			}

			iterator				copy_backward(const_iterator f, const_iterator l, iterator  x);
			template<typename inputit,typename outputit> outputit ucopy(inputit f, inputit l, outputit p)
			{
				for(; f != l; ++p, ++f)
					construct(get_base(p), *f);
				return(p); 
			}

			void					fill(iterator f, const_iterator l, byte x);
			void					ufill(iterator f, size_type n, byte x);

			size_type				distance(const_iterator f, const_iterator l) const;
			template<typename inputit> void _distance(inputit f, inputit l, size_type& n) const
			{
				for(; f != l; ++f)
					++n;
			}

			bool					equal(const_iterator f, const_iterator l, const_iterator x) const;
			bool					lexicographical_compare(const_iterator f1, const_iterator l1,
															const_iterator f2, const_iterator l2) const;
			byte*					allocate(size_type n, const void* hint = 0);
			void					deallocate(void* p, size_type);

			void					construct(byte* p, const_reference v);

			void					_destroy(iterator f, iterator l);
			void					destroy(byte* p);			

			void					outofrange() const;

			iterator mFirst, mLast, mEnd;
	};


#ifndef UNDER_CE_30
	std::ostream &operator<<(std::ostream& os, const Blob& blob);
#endif // UNDER_CE_30


	// --------------------------------------------------------------------------------
	inline bool operator==(const Blob& x, const Blob&y)
	{
		return(x._eq(y));
	}

	inline bool operator!=(const Blob& x, const Blob&y)
	{
		return !(x._eq(y));
	}

	inline bool operator<(const Blob& x, const Blob&y)
	{
		return(x._lt(y));
	}

	inline bool operator>=(const Blob& x, const Blob&y)
	{
		return !(x._lt(y));
	}

	inline bool operator<=(const Blob& x, const Blob&y)
	{
		return(x._eq(y) || x._lt(y));
	}

	inline bool operator>(const Blob& x, const Blob&y)
	{
		return !(x._eq(y) || x._lt(y));
	}

	// --- Implementation

#ifndef NO_STL_SUPPORT
	// --------------------------------------------------------------------------------
	inline Blob::Blob(std::string &str)
		: mFirst(0), mLast(0), mEnd(0)
	{
		const char* str_ptr=str.data();
		insert(begin(), const_iterator(reinterpret_cast<const_pointer>(str_ptr)), const_iterator(reinterpret_cast<const_pointer>(str_ptr+str.length()))); 
	}
#endif //NO_STL_SUPPORT

	// --------------------------------------------------------------------------------
	inline Blob::Blob(const char * str)
		: mFirst(0), mLast(0), mEnd(0)
	{
		const char *end=str;
		while(*end) 
			end++;
		insert(begin(), const_iterator(reinterpret_cast<const_pointer>(str)), const_iterator(reinterpret_cast<const_pointer>(end))); 
	}
	
	// --------------------------------------------------------------------------------
	inline Blob::Blob() 
		: mFirst(0), mLast(0), mEnd(0) 
	{
	}

	// --------------------------------------------------------------------------------
	
	inline Blob::Blob(size_type n, byte v)
	{
		mFirst = allocate(n, (void*)0);		
		ufill(mFirst, n, v);
		mLast = mFirst + n;
		mEnd  = mLast;
	}

	// --------------------------------------------------------------------------------
	inline Blob::Blob(const Blob& x)
	{
		mFirst = allocate(x.size(), (void*)0);
		mLast = ucopy(x.begin(), x.end(), mFirst);
		mEnd = mLast; 
	}

	// --------------------------------------------------------------------------------
	/*inline Blob::Blob(const_iterator f, const_iterator l)
	: mFirst(0), mLast(0), mEnd(0)
	{
		insert(begin(), f, l); 
	}*/

	// --------------------------------------------------------------------------------
	inline Blob::~Blob()
	{
		_destroy(mFirst, mLast);
		deallocate(get_base(mFirst), mEnd - mFirst);
		mFirst = 0, mLast = 0, mEnd = 0; 
	}

	// --------------------------------------------------------------------------------
	inline Blob& Blob::operator=(const Blob& x)
	{
		if(this == &x)
			;
		else if(x.size() <= size())
		{
			iterator s = copy(x.begin(), x.end(), mFirst);
			_destroy(s, mLast);
			mLast = mFirst + x.size(); 
		}
		else if(x.size() <= capacity())
		{
			const_iterator s = x.begin() + size();
			copy(x.begin(), s, mFirst);
			ucopy(s, x.end(), mLast);
			mLast = mFirst + x.size(); 
		}
		else
		{
			_destroy(mFirst, mLast);
			deallocate(get_base(mFirst), mEnd - mFirst);
			mFirst = allocate(x.size(), (void *)0);
			mLast = ucopy(x.begin(), x.end(), mFirst);
			mEnd = mLast; 
		}

		return(*this); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::reserve(size_type n)
	{
		if(capacity() < n)
		{
			iterator s = allocate(n, (void *)0);
			ucopy(mFirst, mLast, s);
			_destroy(mFirst, mLast);
			deallocate(get_base(mFirst), mEnd - mFirst);
			mEnd = s + n;
			mLast = s + size();
			mFirst = s; 
		}
	}

	// --------------------------------------------------------------------------------
	inline Blob::size_type Blob::capacity() const
	{
		return(mFirst == 0 ? 0 : mEnd - mFirst); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::iterator Blob::begin()
	{
		return(mFirst); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::const_iterator Blob::begin() const
	{
		return((const_iterator)mFirst); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::iterator Blob::end()
	{
		return(mLast); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::const_iterator Blob::end() const
	{
		return((const_iterator)mLast); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::reverse_iterator Blob::rbegin()
	{
		return(reverse_iterator(end())); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::const_reverse_iterator Blob::rbegin() const
	{
		return(const_reverse_iterator(end())); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::reverse_iterator Blob::rend()
	{
		return(reverse_iterator(begin())); 
	}

	// --------------------------------------------------------------------------------			
	inline Blob::const_reverse_iterator Blob::rend() const
	{
		return(const_reverse_iterator(begin())); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::resize(size_type n, byte x)
	{
		if(size() < n)
			insert(end(), n - size(), x);
		else if(n < size())
			erase(begin() + n, end()); 
	}
	
	// --------------------------------------------------------------------------------
	inline Blob::size_type Blob::size() const
	{
		return(mFirst == 0 ? 0 : mLast - mFirst);
	}

	// --------------------------------------------------------------------------------
	inline Blob::size_type Blob::max_size() const
	{
		size_type n = (size_type)(-1) / sizeof(byte);
		return(0 < n ? n : 1); 
	}

	// --------------------------------------------------------------------------------
	inline bool Blob::empty() const
	{
		return(size() == 0); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::const_reference Blob::at(size_type p) const
	{
		if(size() <= p)
			outofrange();
		return(*(begin() + p)); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::reference Blob::at(size_type p)
	{
		if(size() <= p)
			outofrange();
		return(*(begin() + p)); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::const_reference Blob::operator[](size_type p) const
	{
		return(*(begin() + p)); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::reference Blob::operator[](size_type p)
	{
		return(*(begin() + p)); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::reference Blob::front()
	{
		return(*begin()); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::const_reference Blob::front() const
	{
		return(*begin()); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::reference Blob::back()
	{
		return(*(end() - 1)); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::const_reference Blob::back() const
	{
		return(*(end() - 1)); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::push_back(byte x)
	{
		insert(end(), x); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::pop_back()
	{
		erase(end() - 1); 
	}

	/*
	// --------------------------------------------------------------------------------
	inline void Blob::assign(const_iterator f, const_iterator l)
	{
		erase(begin(), end());
		insert(begin(), f, l); 
	}
	*/

	// --------------------------------------------------------------------------------
	inline void Blob::assign(size_type n, byte x)
	{
		erase(begin(), end());
		insert(begin(), n, x); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::iterator Blob::insert(iterator p, byte x)
	{
		size_type o = p - begin();
		insert(p, 1, x);
		return(begin() + o); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::insert(iterator p, size_type m, byte x)
	{
		if(size_type(mEnd - mLast) < m)
		{
			size_type n = size() + (m < size() ? size() : m);
			iterator s = allocate(n, (void *)0);
			iterator q = ucopy(mFirst, p, s);
			ufill(q, m, x);
			ucopy(p, mLast, q + m);
			_destroy(mFirst, mLast);
			deallocate(get_base(mFirst), mEnd - mFirst);
			mEnd = s + n;
			mLast = s + size() + m;
			mFirst = s; 
		}
		else if(size_type(mLast - p) < m)
		{
			ucopy(p, mLast, p + m);
			ufill(mLast, m - (mLast - p), x);
			fill(p, mLast, x);
			mLast += m; 
		}
		else if(0 < m)
		{
			ucopy(mLast - m, mLast, mLast);
			copy_backward(p, mLast - m, mLast);
			fill(p, p + m, x);
			mLast += m; 
		}
	}

	/*
	// --------------------------------------------------------------------------------
	inline void Blob::insert(iterator p, const_iterator f, const_iterator l)
	{
		size_type m = 0;
		_distance(f, l, m);
		if(size_type(mEnd - mLast) < m) 
		{
			size_type n = size() + (m < size() ? size() : m);
			iterator s = allocate(n, (void *)0);
			iterator q = ucopy(mFirst, p, s);
			q = ucopy(f, l, q);
			ucopy(p, mLast, q);
			_destroy(mFirst, mLast);
			deallocate(mFirst, mEnd - mFirst);
			mEnd = s + n;
			mLast = s + size() + m;
			mFirst = s; 
		}
		else if(size_type(mLast - p) < m) 
		{
			ucopy(p, mLast, p + m);
			ucopy(f + (mLast - p), l, mLast);
			copy(f, f + (mLast - p), p);
			mLast += m; 
		}
		else if(0 < m) 
		{
			ucopy(mLast - m, mLast, mLast);
			copy_backward(p, mLast - m, mLast);
			copy(f, l, p);
			mLast += m; 
		}
	}
	*/

	// --------------------------------------------------------------------------------
	inline void Blob::append(const Blob& x)
	{
		insert(end(), x.begin(), x.end());
	}

	// --------------------------------------------------------------------------------
	inline void Blob::append(size_type m, byte x)
	{
		insert(end(), m, x);
	}

	// --------------------------------------------------------------------------------
	inline Blob::iterator Blob::erase(iterator p)
	{
		copy(p + 1, end(), p);
		_destroy(mLast - 1, mLast);
		--mLast;
		return(p); 
	}

	// --------------------------------------------------------------------------------
	inline Blob::iterator Blob::erase(iterator f, iterator l)
	{
		iterator s = copy(l, end(), f);
		_destroy(s, end());
		mLast = s;
		return(f); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::clear()
	{
		erase(begin(), end()); 
	}

	// --------------------------------------------------------------------------------
	inline bool Blob::_eq(const Blob& x) const	
	{
		return(size() == x.size()	&& equal(begin(), end(), x.begin())); 
	}

	// --------------------------------------------------------------------------------
	inline bool Blob::_lt(const Blob& x) const	
	{
		return(lexicographical_compare(begin(), end(), x.begin(), x.end())); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::swap(Blob& x)	
	{
		if(/*get_allocator() == x.get_allocator()*/ true) 
		{
			// swap control information
			std::swap(mFirst, x.mFirst);
			std::swap(mLast, x.mLast);
			std::swap(mEnd, x.mEnd);
		}
		else
		{
			// different allocator, do multiple assigns
			Blob Ts = *this; 
			*this = x, 
			x = Ts;
		}
	}

	// --------------------------------------------------------------------------------
	inline void Blob::_destroy(iterator f, iterator l)
	{
		for(; f != l; ++f)
			destroy(get_base(f));
	}


	// --------------------------------------------------------------------------------
	inline void Blob::ufill(iterator f, size_type n, byte x)
	{
		for(; 0 < n; --n, ++f)
			construct(get_base(f), x); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::outofrange() const
	{
		throw( OutOfRangeException("invalid Blob subscript","Blob::outofrange"));
	}

	// --------------------------------------------------------------------------------
	inline Blob::iterator Blob::copy_backward(const_iterator f, const_iterator l, iterator  x)
	{
		while(f != l)
			*--x = *--l;
		return(x); 
	}

	// --------------------------------------------------------------------------------
	inline void Blob::fill(iterator f, const_iterator l, byte x)
	{
		for(; get_base(f) != get_base(l); ++f)
			*f = x; 
	}

	// --------------------------------------------------------------------------------
	inline Blob::size_type Blob::distance(const_iterator f, const_iterator l) const 
	{
		size_type n = 0;
		_distance(f, l, n);
		return(n); 
	}


	// --------------------------------------------------------------------------------
	inline bool Blob::equal(const_iterator f, const_iterator l, const_iterator x) const
	{
		for(; f != l && *f == *x; ++f, ++x)
			;
		return f == l;
	}

	// --------------------------------------------------------------------------------
	inline bool Blob::lexicographical_compare(const_iterator f1, const_iterator l1,
											  const_iterator f2, const_iterator l2) const
	{
		for(; f1 != l1 && f2 != l2; ++f1, ++f2)
			if(*f1 < *f2)
				return(true);
			else if(*f2 < *f1)
				return(false);
		return(f1 == l1 && f2 != l2); 
	}



	// --------------------------------------------------------------------------------
	inline void Blob::construct(byte* p, const_reference v) 
	{
		*p = v;
	}

	// --------------------------------------------------------------------------------
	inline void Blob::destroy(byte* p)
	{
		*p = 0;
	}

} // namespace act

#endif // ACT_BLOB_H
