#ifndef LAYERED_BIASED_NET_H
#define LAYERED_BIASED_NET_H

#include "layered_net.h"
#include <vector>
#include <string>

class unit
{
public:
	float out, delta;
	unit(float o = 0.0f, float d = 0.0f) : out(o), delta(d) {}
};

class layeredBiasedNet : public layeredNet
{
private:
	float learning_rate;	// coefficiente di apprendimento
	float momentum_coeff;	// coefficiente d'inerzia per l'apprendimento
	static const float bias_value;

protected:
	virtual void store(const std::vector<float>& in) /*override*/;
	virtual void linkLayer(layers_iterator l) /*override*/;

public:
	explicit layeredBiasedNet(float lr = 0.5f, float m = 0.2f);
	layeredBiasedNet(std::string netfile, float lr = 0.5f, float m = 0.2f);
	layeredBiasedNet& operator=(const layeredBiasedNet& net);

	bool is_bias(unsigned int n) const;
	virtual unsigned int input_size() const /*override*/;
	float learningRate() const;
	float momentum() const;

	void init(float bound = 0.5f);
	void init(std::string netfile);
	virtual void addLayer(unsigned int n_nodes) /*override*/;

	virtual std::vector<float> operator()(const std::vector<float>& in = std::vector<float>()) /*override*/;

	void train(const std::vector<std::vector<float> >& examples, const std::vector<std::vector<float> >& targets, float& error, unsigned int max_epochs = 28000);
	void train(std::string data_file, float& error, unsigned int max_epochs = 28000);
};

#endif
