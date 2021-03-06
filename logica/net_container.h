#ifndef NET_CONTAINER_H
#define NET_CONTAINER_H

#include "network.h"

class netContainer
{
	friend class iterator;
	friend class const_iterator;

private:
	unsigned int sz;
	unsigned int cpty;
	network ** nets;

	void resize(unsigned int new_size);
	void reserve(unsigned int new_capacity);

public:
	netContainer();
	~netContainer();
	netContainer(const netContainer& net);
	netContainer& operator=(const netContainer& net);

	class iterator
	{
	private:
		network ** punt;
	public:
		iterator(network ** p = nullptr);
		network * operator*() const;
		bool operator==(const iterator& it) const;
		bool operator!=(const iterator& it) const;
		bool operator<(const iterator& it) const;
		iterator& operator++();
		iterator operator++(int);
	};

	class const_iterator : public iterator
	{
	public:
		const network * operator*() const;
	};

	iterator begin() const;
	iterator end() const;
	unsigned int size() const;

	void push_back(network * net);			// inserisce il puntatore a net nella rete
	void pop_back(unsigned int n = 1);		// rimuovi gli ultimi n nodi immessi
	network * operator[](int i) const;
	void clear();
};

#endif
