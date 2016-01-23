#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "dag.h"

class network : public DAG
{
private:
	std::map<unsigned int, float> input_map;
	virtual float activation_function(float x) const;

protected:
	float neuron(unsigned int index) const;
	virtual void store(const std::vector<float>& in);

public:
	network(unsigned int s = 0);
	network(std::string netfile);
	network(const network& net);

	enum init_t { ZERO, RAND };
	void init(init_t mode = RAND, float bound = 0.5f);
	void init(std::string netfile);
	void save(std::string netfile = "untitled.net") const;

	bool is_output(unsigned int node) const;
	bool is_input(unsigned int node) const;
	bool is_connected(unsigned int node) const;
	unsigned int input_size() const;

	std::vector<float> operator()(const std::vector<float>& in);
};

std::ostream& operator<<(std::ostream& os, const network& net);
std::istream& operator>>(std::istream& is, const network& net);

#endif