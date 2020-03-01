#ifndef __TDEE_H__
#define __TDEE_H__
/*
 * Copyright (C) 2019 by Joseph A. Marrero. http://joemarrero.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

static inline double pounds2kilograms(double pounds)
{
	return pounds / 2.20462;
}

static inline double inches2centimeters(double inches)
{
	return inches * 2.54;
}

static inline double basal_metabolic_rate_for_men(double age_in_years, double weight_in_kg, double height_in_cm)
{
	#ifdef HARRIS_BENEDICT_BMR_1919
	return 66.47 + (13.75 * weight_in_kg) + (5.003 * height_in_cm) - (6.755 * age_in_years);
	#else
	return (10 * weight_in_kg) + (6.25 * height_in_cm) - (5 * age_in_years) + 5;
	#endif
}

static inline double basal_metabolic_rate_for_women(double age_in_years, double weight_in_kg, double height_in_cm)
{
	#ifdef HARRIS_BENEDICT_BMR_1919
	return 655.1 + (9.563 * weight_in_kg) + (1.85 * height_in_cm) - (4.676 * age_in_years);
	#else
	return (10 * weight_in_kg) + (6.25 * height_in_cm) - (5 * age_in_years) - 161;
	#endif
}


static inline double physical_activity_level_sedentary(double bmr)
{
	return bmr * 1.53;
}

static inline double physical_activity_level_moderately_active(double bmr)
{
	return bmr * 1.76;
}

static inline double physical_activity_level_vigorously_active(double bmr)
{
	return bmr * 2.25;
}

/*
 * Formula from the Journal of Sports Sciences provide the calorie expenditure calculations for men.
 */
static inline double calorie_expenditure_for_men(double age_in_years, double weight_in_kg, double average_heart_rate, double time_in_mins)
{
	double weight_in_lbs = pounds2kilograms(weight_in_kg);
	return (((0.6309 * average_heart_rate) - (0.09036 * weight_in_lbs) + (0.2017 * age_in_years) - 55.0969) * time_in_mins) / 4.184;
}

/*
 * Formula from the Journal of Sports Sciences provide the calorie expenditure calculations for women.
 */
static inline double calorie_expenditure_for_women(double age_in_years, double weight_in_kg, double average_heart_rate, double time_in_mins)
{
	double weight_in_lbs = pounds2kilograms(weight_in_kg);
	return (((0.4472 * average_heart_rate) - (0.05741 * weight_in_lbs) + (0.074 * age_in_years) - 20.4022) * time_in_mins) / 4.184;
}

#endif /* __TDEE_H__ */
