#include "layered_biased_net.h"
#include <algorithm>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <iostream>	// debugging

using std::vector;



void layeredBiasedNet::incremental_training(const vector<vector<float> >& examples, const vector<vector<float> >& targets, float& error, const unsigned int max_epochs)
{
	vector<unit> units(size());
	vector<float> momentum_terms(n_layers(), 0.0f);
	vector<unsigned int> inds;
	for (unsigned int i = 0; i < examples.size(); ++i)
		inds.push_back(i);
	float tot_err = 0.0f;
	unsigned int epoch = 0;

	do
	{
		tot_err = 0.0f;
		++epoch;
		std::cout << "\r[" << epoch << "]\t";

		std::random_shuffle(inds.begin(), inds.end());

		for (auto e = inds.begin(); e < inds.end(); ++e)	// --- per ogni esempio:
		{
			// --- per ogni neurone, calcola il flusso a partire dall'esempio:

			store(examples[*e]);
			for (layers_iterator l = begin(); l < end(); ++l)
				for (nodes_iterator i = begin(l); i < end(l); ++i)
					units[i].out = neuron(i);

			// (SI PUO MIGLIORARE!)  ^^^^^

//			std::cout << "(";
//			for (nodes_iterator i = begin(end() - 1); i < end(end() - 1); ++i)
//				std::cout << units[i].out << ", ";
//			std::cout << "\b\b)\t";



			// --- per ogni unità, calcola l'errore:

			float err = 0.0f;
			unsigned int t = 0;
			for (nodes_iterator i = begin(end() - 1) + 1; i < end(end() - 1); ++i)
			{
				units[i].delta = activation_derivative(units[i].out) * (targets[*e][t] - units[i].out);		// (senza derivata va meglio...!)
				err += fabs(targets[*e][t] - units[i].out);
				// forse è meglio l'err quadratico medio...
				++t;
			}
			err /= output_size() - 1;
//			std::cout << err << '\n';

			for (layers_iterator l = end() - 2; l >= begin(); --l)
				for (nodes_iterator i = begin(l) + 1; i < end(l); ++i)
				{
					float downstream = 0.0f;
					for (nodes_iterator j = begin(l + 1); j < end(l + 1); ++j)
						downstream += edge(i, j) * units[j].delta;
					units[i].delta = activation_derivative(units[i].out) * downstream;
				}



			// --- aggiorna i collegamenti sinaptici:

			for (layers_iterator l = begin(); l < end() - 1; ++l)
				for (nodes_iterator i = begin(l) + !bias_plasticity; i < end(l); ++i)
					for (nodes_iterator j = begin(l + 1); j < end(l + 1); ++j)
						if (edge(i, j))
						{
							float update = learningRate() * units[j].delta * units[i].out + momentum() * momentum_terms[l];
							if (edge(i, j) + update != 0)
								link(i, j, edge(i, j) + update);
							else
								link(i, j, 0.0000001f);	// <<< un po' troppo artigianale
							//  --------------------------------------------------------
							momentum_terms[l] = update;
						}

			tot_err += err;
		}
		tot_err /= examples.size();
		std::cout << "error: " << tot_err;
	} while (tot_err > error && epoch < max_epochs);

	error = tot_err;
	std::cout << '\n';
}

void layeredBiasedNet::incremental_training(const std::string data_file, float& error, const unsigned int max_epochs)
{
	std::ifstream fin(data_file);
	unsigned int n_ex = 0, n_in = 0, n_out = 0;
	fin >> n_ex >> n_in >> n_out;

	vector<vector<float> > examples(n_ex, vector<float>(n_in));
	vector<vector<float> > targets(n_ex, vector<float>(n_out));
	for (unsigned int e = 0; e < n_ex; ++e)
	{
		for (unsigned int i = 0; i < n_in; ++i)
			fin >> examples[e][i];
		for (unsigned int i = 0; i < n_out; ++i)
			fin >> targets[e][i];
	}

	fin.close();

	incremental_training(examples, targets, error, max_epochs);
}