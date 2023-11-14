#ifndef __RANDOMNUMBERGENERATOR_H__
#define __RANDOMNUMBERGENERATOR_H__

class RandomNumberGenreator
{
public:
	RandomNumberGenreator();

	float GetRandomNumber();

private:
	int m_arand;

	unsigned int m_seed;

	float m_addition;
	float m_numerator;
	float m_denominator;
};

#endif
