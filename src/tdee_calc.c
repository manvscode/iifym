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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <xtd/console.h>
#include <collections/vector.h>
#include "tdee.h"

#define VERSION  "1.0"

static void banner( void );
static void about( int argc, char* argv[] );

typedef enum {
	SEX_MALE = 0,
	SEX_FEMALE,
} sex_t;

//typedef enum {
	//AL_SEDENTARY = 0,
//} activity_level_t;

typedef struct {
	double age;
	double height;
	double weight;
	sex_t sex;
	int gym_days;
	int time_in_gym;
	int average_heartrate;
	//activity_level_t activity_level;
	bool use_metric;
	bool verbose;
} app_args_t;

int main( int argc, char* argv[] )
{
	int result = 0;

	setlocale( LC_ALL, "" );

	app_args_t args = {
		.age               = 18,
		.height            = 5.0 * 12 + 6.0,
		.weight            = 200,
		.sex               = SEX_MALE,
		.gym_days          = 3,
		.time_in_gym       = 60,
		.average_heartrate = 120,
		.use_metric        = false,
		.verbose           = false
	};

	if( argc > 0 )
	{
		for( int arg = 1; arg < argc; )
		{
			if( strcmp( "-a", argv[arg] ) == 0 || strcmp( "--age", argv[arg] ) == 0 )
			{
				int last_arg = arg + 1;

				if( last_arg < argc )
				{
					args.age = strtod(argv[arg + 1], &argv[arg + 1]);
					// TODO: validation
					arg += 2;
				}
				else
				{
					fwprintf( stderr, L"[ERROR] Missing required argument for age option.\n" );
					result = -1;
					goto done;
				}
			}
			else if( strcmp( "-H", argv[arg] ) == 0 || strcmp( "--height", argv[arg] ) == 0 )
			{
				int last_arg = arg + 1;

				if( last_arg <= argc )
				{
					args.height = strtod(argv[arg + 1], &argv[arg + 1]);
					// TODO: validation
					arg += 2;
				}
				else
				{
					fwprintf( stderr, L"[ERROR] Missing required argument for height option.\n" );
					result = -1;
					goto done;
				}
			}
			else if( strcmp( "-w", argv[arg] ) == 0 || strcmp( "--weight", argv[arg] ) == 0 )
			{
				int last_arg = arg + 1;
				if( last_arg < argc )
				{
					args.weight = strtod(argv[arg + 1], &argv[arg + 1]);
					// TODO: validation
					arg += 2;
				}
				else
				{
					fwprintf( stderr, L"[ERROR] Missing required argument for weight option.\n" );
					result = -1;
					goto done;
				}
			}
			else if( strcmp( "-s", argv[arg] ) == 0 || strcmp( "--sex", argv[arg] ) == 0 )
			{
				int last_arg = arg + 1;
				if( last_arg < argc )
				{
					int sex = tolower(*argv[arg + 1]);
					if(sex == 'm')
					{
						args.sex = SEX_MALE;
					}
					else if( sex == 'f')
					{
						args.sex = SEX_FEMALE;
					}
					else
					{
						fwprintf( stderr, L"[ERROR] Expecting 'm' or '0' for male and 'w', 'f' or '1' for female.\n" );
						result = -1;
						goto done;
					}
					arg += 2;
				}
				else
				{
					fwprintf( stderr, L"[ERROR] Missing required argument for sex option.\n" );
					result = -1;
					goto done;
				}
			}
			else if( strcmp( "-d", argv[arg] ) == 0 || strcmp( "--gym-days", argv[arg] ) == 0 )
			{
				int last_arg = arg + 1;
				if( last_arg < argc )
				{
					args.gym_days = strtol(argv[arg + 1], &argv[arg + 1], 10);
					// TODO: validation
					arg += 2;
				}
				else
				{
					fwprintf( stderr, L"[ERROR] Missing required argument for gym days option.\n" );
					result = -1;
					goto done;
				}
			}
			else if( strcmp( "-t", argv[arg] ) == 0 || strcmp( "--gym-time", argv[arg] ) == 0 )
			{
				int last_arg = arg + 1;
				if( last_arg < argc )
				{
					args.time_in_gym = strtol(argv[arg + 1], &argv[arg + 1], 10);
					// TODO: validation
					arg += 2;
				}
				else
				{
					fwprintf( stderr, L"[ERROR] Missing required argument for time in gym option.\n" );
					result = -1;
					goto done;
				}
			}
			else if( strcmp( "-r", argv[arg] ) == 0 || strcmp( "--heart-rate", argv[arg] ) == 0 )
			{
				int last_arg = arg + 1;
				if( last_arg < argc )
				{
					args.average_heartrate = strtol(argv[arg + 1], &argv[arg + 1], 10);
					// TODO: validation
					arg += 2;
				}
				else
				{
					fwprintf( stderr, L"[ERROR] Missing required argument for average heart rate option.\n" );
					result = -1;
					goto done;
				}
			}
			else if( strcmp( "-m", argv[arg] ) == 0 || strcmp( "--use-metric", argv[arg] ) == 0 )
			{
				args.use_metric = true;
				arg += 1;
			}
			else if( strcmp( "-v", argv[arg] ) == 0 || strcmp( "--verbose", argv[arg] ) == 0 )
			{
				args.verbose = true;
				arg += 1;
			}
			else
			{
				wconsole_fg_color_256( stderr, CONSOLE_COLOR256_RED );
				wprintf(L"\n");
				fwprintf( stderr, L"ERROR: " );
				wconsole_reset( stderr );
				fwprintf( stderr, L"Unrecognized command line option '%s'\n", argv[arg] );
				about( argc, argv );
				result = -2;
				goto done;
			}
		}
	}

	banner();
	//wprintf(L"\n");

	double weight_kg = 0.0;
	double height_cm = 0.0;

	if( !args.use_metric )
	{
		weight_kg = pounds2kilograms(args.weight);
		height_cm = inches2centimeters(args.height);
	}
	else
	{
		weight_kg = args.weight;
		height_cm = args.height;
	}

	double bmr = 0.0;
	double average_energy_expenditure = 0.0;

	if( args.sex == SEX_MALE )
	{
		bmr = basal_metabolic_rate_for_men(args.age, weight_kg, height_cm);
		average_energy_expenditure = (int) round(args.gym_days * calorie_expenditure_for_men(args.age, weight_kg, args.average_heartrate, args.time_in_gym) / 7.0);
	}
	else
	{
		bmr = basal_metabolic_rate_for_women(args.age, weight_kg, height_cm);
		average_energy_expenditure = args.gym_days * calorie_expenditure_for_women(args.age, weight_kg, args.average_heartrate, args.time_in_gym) / 7.0;
	}

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf(L"\u250c");
	for(int i = 0; i < 37; i++) wprintf(L"\u2500");
	wprintf(L"\u2510\n");
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wprintf(L"            Sex: %-20s", args.sex == SEX_MALE ? "male" : "female");
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wchar_t age_string[32];
	swprintf(age_string, sizeof(age_string) / sizeof(wchar_t), L"%.1lf years", args.age);
	wprintf(L"            Age: %-20ls", age_string);
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wchar_t height_string[32];
	swprintf(height_string, sizeof(height_string) / sizeof(wchar_t), L"%.1lf %s", args.height, args.use_metric ? "cm" : "inches");
	wprintf(L"         Height: %-20ls", height_string);
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wchar_t weight_string[32];
	swprintf(weight_string, sizeof(weight_string) / sizeof(wchar_t), L"%.1lf %s", args.weight, args.use_metric ? "kg" : "lbs");
	wprintf(L"         Weight: %-20ls", weight_string);
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wchar_t weekly_gym_days[48];
	swprintf(weekly_gym_days, sizeof(weekly_gym_days) / sizeof(wchar_t), L"%d days", args.gym_days);
	wprintf(L"       Gym Days: %-20ls", weekly_gym_days);
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wchar_t weekly_gym_time[48];
	swprintf(weekly_gym_time, sizeof(weekly_gym_time) / sizeof(wchar_t), L"%d mins", args.time_in_gym);
	wprintf(L"  Work-out Time: %-20ls", weekly_gym_time);
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wchar_t average_heart_rate[48];
	swprintf(average_heart_rate, sizeof(average_heart_rate) / sizeof(wchar_t), L"%d bpm", args.average_heartrate);
	wprintf(L" Avg. Heartrate: %-20ls", average_heart_rate);
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );





	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wchar_t energy_expenditure_string[32];
	swprintf(energy_expenditure_string, sizeof(energy_expenditure_string) / sizeof(wchar_t), L"%d cals", (int) round(average_energy_expenditure));
	wprintf(L"  Avg. Work-Out: %-20ls", energy_expenditure_string);
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );





	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf(L"\u251c");
	for(int i = 0; i < 37; i++) wprintf(L"\u2500");
	wprintf(L"\u2524\n");
	wconsole_reset( stdout );


	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wprintf(L"   BMR Calories: %'-20d", (int) round(bmr));
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );


	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf(L"\u251c");
	for(int i = 0; i < 37; i++) wprintf(L"\u2500");
	wprintf(L"\u2524\n");
	wconsole_reset( stdout );


	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wprintf(L"      Cutting Calories: %'-13d", (int) round(physical_activity_level_sedentary(bmr) + average_energy_expenditure - 500));
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wprintf(L" Maintainance Calories: %'-13d", (int) round(physical_activity_level_sedentary(bmr) + average_energy_expenditure));
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502" );
	wconsole_reset( stdout );
	wprintf(L"      Bulking Calories: %'-13d", (int) round(physical_activity_level_sedentary(bmr) + average_energy_expenditure + 500));
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf( L"\u2502\n" );
	wconsole_reset( stdout );

	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_GREY_15);
	wprintf(L"\u2514");
	for(int i = 0; i < 37; i++) wprintf(L"\u2500");
	wprintf(L"\u2518\n");
	wconsole_reset( stdout );

done:
	return result;
}

void banner( void )
{
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_RED );
	wprintf(L"      ___________ _____ _____ \n");
	wprintf(L"     |_   _|  _  \\  ___|  ___|\n");
	wprintf(L"       | | | | | | |__ | |__  \n");
	wprintf(L"       | | | | | |  __||  __| \n");
	wprintf(L"       | | | |/ /| |___| |___ \n");
	wprintf(L"       \\_/ |___/ \\____/\\____/ \n");
	wconsole_reset( stdout );
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_YELLOW );
	wprintf(L"             Calculator\n");
	wconsole_reset( stdout );
}

void about( int argc, char* argv[] )
{
	banner();
	wprintf(L" Copyright (c) 2019, Joe Marrero.\n");
	wprintf(L"     http://joemarrero.com/\n");
	wprintf(L"\n");

	wprintf(L"Example Usage:\n");
	wprintf(L"    %s -a 18 -w 165 -H 66 -s m\n", argv[0]);
	wprintf(L"\n\n");

	wprintf(L"Command Line Options:\n");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-a", "--age", "The age in years.");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-H", "--height", "The height in inches or centimeters.");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-w", "--weight", "The weight in pounds or kilograms.");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-s", "--sex", "The sex (male or female).");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-m", "--use-metric", "The units are metric and not imperial.");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-d", "--gym-days", "The number of days in a week with weight-training.");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-t", "--gym-time", "The number of minutes spent per work-out.");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-r", "--heart-rate", "The average heart rate during work-outs.");
	wprintf(L"    %-2s, %-12s   %-50s\n", "-h", "--help", "Show program usage.");
	wprintf(L"\n\n");

	wprintf(L"If you found this utility useful, please consider making a donation\n");
	wprintf(L"of bitcoin to: ");
	wconsole_fg_color_256( stdout, CONSOLE_COLOR256_MAGENTA);
	wprintf(L"3A5M1m2BNSBgo9V7B8wf6VtWQDMMgp5abZ");
	wconsole_reset( stdout);
	wprintf(L"\n\n");
	wprintf(L"All donations help cover maintenance costs and are much appreciated.\n");

	wprintf(L"\n");
}

