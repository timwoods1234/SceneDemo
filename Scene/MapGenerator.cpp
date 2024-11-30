#include "MapGenerator.h"
#include "GaussGen.h"
#include "FractalData.h"
#include "FractalParams.h"

//-------------------------------------------------------------------------------
void MapGenerator::Generate(const FractalParams& params, FractalData& data)
{
	GaussGen gaussianGenerator;

	double delta;
	int count, stage;
	int width, height, end, start;

	double two = 2;
	double max = params.scale;
	count = (int)pow(two, max);

	delta = params.standardDeviation;
	
	data.Clear();
	data.SetSize(count + 1, count + 1);

	// Init starting corner points in grid
	data.Set(0, 0,			delta * gaussianGenerator.GaussianNumber());
	data.Set(0, count,		delta * gaussianGenerator.GaussianNumber());
	data.Set(count, 0,		delta * gaussianGenerator.GaussianNumber());
	data.Set(count, count,	delta * gaussianGenerator.GaussianNumber());

	end = count;
	start = count / 2;
	stage = 1;
	double average = 0.f;
	
	while (stage <= params.scale)
	{
		// (1) generate middle values using average of corners
		delta = delta * pow(0.5, 0.5 * params.shape);

		for (width = start; width <= count - start; width += end)
		{
			for (height = start; height <= count - start; height += end)
			{
				average = Compute4(
					gaussianGenerator,
					delta,
					data.Get(width + start, height + start),
					data.Get(width + start, height - start),
					data.Get(width - start, height + start),
					data.Get(width - start, height - start));

				data.Set(width, height, average);
			}
		}

		// random addition across the grid
		if (params.useAddition)
		{
			for (width = 0; width <= count; width += end)
			{
				for (height = 0; height <= count; height += end)
				{
					data.Set(width, height, data.Get(width, height) + delta * gaussianGenerator.GaussianNumber());
				}
			}
		}

		// (2) generate outside edges
		delta = delta * pow(0.5, 0.5 * params.shape);

		for (width = start; width <= count - start; width += end)
		{
			average = Compute3(gaussianGenerator, delta, data.Get(width + start, 0), data.Get(width - start, 0), data.Get(width, start));
			data.Set(width, 0, average);

			average = Compute3(gaussianGenerator, delta, data.Get(width + start, count), data.Get(width - start, count), data.Get(width, count - start));
			data.Set(width, count, average);

			average = Compute3(gaussianGenerator, delta, data.Get(0, width + start), data.Get(0, width - start), data.Get(start, width));
			data.Set(0, width, average);

			average = Compute3(gaussianGenerator, delta, data.Get(count, width + start), data.Get(count, width - start), data.Get(count - start, width));
			data.Set(count, width, average);
		}

		// (3) generate inner edges (horizontally)
		for (width = start; width <= count - start; width += end)
		{
			for (height = end; height <= count - start; height += end)
			{
				average = Compute4(gaussianGenerator, delta, data.Get(width, height + start), data.Get(width, height - start), data.Get(width + start, height), data.Get(width - start, height));
				data.Set(width, height, average);
			}
		}

		// (4) and vertically
		for (width = end; width <= count - start; width += end)
		{
			for (height = start; height <= count - start; height += end)
			{
				average = Compute4(gaussianGenerator, delta, data.Get(width, height + start), data.Get(width, height - start), data.Get(width + start, height), data.Get(width - start, height));

				data.Set(width, height, average);
			}
		}

		// random addition across the grid
		if (params.useAddition)
		{
			for (width = 0; width <= count; width += end)
			{
				for (height = 0; height <= count; height += end)
				{
					data.Set(width, height, data.Get(width, height) + delta * gaussianGenerator.GaussianNumber());
				}
			}

			for (width = start; width <= count - start; width += end)
			{
				for (height = start; height <= count - start; height += end)
				{
					data.Set(width, height, data.Get(width, height) + delta * gaussianGenerator.GaussianNumber());
				}
			}
		}

		// reduce size of area and start again
		end = end / 2;
		start = start / 2;

		stage++;
	}

	for (int index = 0; index < params.smoothCount; index++)
	{
		ApplySmoothing(gaussianGenerator, data);
	}

	data.Finalize();
}

//-------------------------------------------------------------------------------
double MapGenerator::Compute3(GaussGen& generator, double delta, double x0, double x1, double x2)
{
	return ((x0 + x1 + x2) / 3 + delta * generator.GaussianNumber());
}

//-------------------------------------------------------------------------------
double MapGenerator::Compute4(GaussGen& generator, double delta, double x0, double x1, double x2, double x3)
{
	return ((x0 + x1 + x2 + x3) / 4 + delta * generator.GaussianNumber());
}

//-------------------------------------------------------------------------------
void MapGenerator::ApplySmoothing(GaussGen& generator, FractalData& data)
{
	for (unsigned int h = 1; h < data.GetHeight() - 1; h++)
	{
		for (unsigned int w = 1; w < data.GetWidth() - 1; w++)
		{
			double average = Compute4(
				generator, 0.f,
				data.Get(w - 1, h),
				data.Get(w + 1, h),
				data.Get(w, h - 1),
				data.Get(w, h + 1));

			data.Set(w, h, average);
				
		}
	}
}