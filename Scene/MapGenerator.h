#ifndef __MAPGENERATOR_H__
#define __MAPGENERATOR_H__

class GaussGen;
class FractalData;
struct FractalParams;

class MapGenerator
{
public:
	void Generate(const FractalParams& params, FractalData& data);

private:

	void ApplySmoothing(GaussGen& generator, FractalData& data);

	double Compute3(GaussGen& generator, double delta, double x0, double x1, double x2);

	double Compute4(GaussGen& generator, double delta, double x0, double x1, double x2, double x3);
};

#endif
