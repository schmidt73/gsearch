#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <inttypes.h>

#include "settings.h"
#include "options.h"

static char* optstring = "hs:n:N:l:c:t:d:";

static struct option long_opts[] = {
        {"search", required_argument, NULL, 's'},
        {"numresults", required_argument, NULL, 'n'},
        {"startresult", required_argument, NULL, 'N'},
        {"lang", required_argument, NULL, 'l'},
        {"country", required_argument, NULL, 'c'},
        {"time", required_argument, NULL, 't'},
        {"searchintitle", no_argument, NULL, 0},
        {"displaymode", required_argument, NULL, 'd'},
        {"help", no_argument, NULL, 'h'},
};

char* valid_countries[] = {
        "AF", "AL", "DZ", "AS", "AD", "AO", "AI", "AQ", "AG", "AR",
        "AM", "AW", "AU", "AT", "AZ", "BS", "BH", "BD", "BB", "BY",
        "BE", "BZ", "BJ", "BM", "BT", "BO", "BA", "BW", "BV", "BR",
        "IO", "BN", "BG", "BF", "BI", "KH", "CM", "CA", "CV", "KY",
        "CF", "TD", "CL", "CN", "CX", "CC", "CO", "KM", "CG", "CD",
        "CK", "CR", "CI", "HR", "CY", "CZ", "DK", "DJ", "DM", "DO",
        "TL", "EC", "EG", "SV", "GQ", "ER", "EE", "ET", "FK", "FO",
        "FJ", "FI", "FR", "GF", "PF", "TF", "GA", "GM", "GE", "DE",
        "GH", "GI", "GR", "GL", "GD", "GP", "GU", "GT", "GN", "GW",
        "GY", "HT", "HM", "HN", "HK", "HU", "IS", "IN", "ID", "IQ",
        "IE", "IL", "IT", "JM", "JP", "JO", "KZ", "KE", "KI", "KW",
        "KG", "LA", "LV", "LB", "LS", "LR", "LY", "LI", "LT", "LU",
        "MO", "MK", "MG", "MW", "MY", "MV", "ML", "MT", "MH", "MQ",
        "MR", "MU", "YT", "MX", "FM", "MD", "MC", "MN", "MS", "MA",
        "MZ", "NA", "NR", "NP", "NL", "AN", "NC", "NZ", "NI", "NE",
        "NG", "NU", "NF", "MP", "NO", "OM", "PK", "PW", "PS", "ZW",
        "PA", "PG", "PY", "PE", "PH", "PN", "PL", "PT", "PR", "QA",
        "RE", "RO", "RU", "RW", "KN", "LC", "VC", "WS", "SM", "ST",
        "SA", "SN", "CS", "SC", "SL", "SG", "SK", "SI", "SB", "SO",
        "ZA", "GS", "KR", "ES", "LK", "SH", "PM", "SR", "SJ", "SZ",
        "SE", "CH", "TW", "TJ", "TZ", "TH", "TG", "TK", "TO", "TT",
        "TN", "TR", "TM", "TC", "TV", "UG", "UA", "AE", "GB", "US",
        "UM", "UY", "UZ", "VU", "VA", "VE", "VN", "VG", "VI", "WF",
        "EH", "YE", "ZM", 
};

char* valid_langs[] = {
        "ar", "hy", "be", "bg", "ca", "hr", "cs", "da", "nl", "en",
        "eo", "et", "tl", "fi", "fr", "de", "el", "iw", "hu", "is",
        "id", "it", "ja", "ko", "lv", "lt", "no", "fa", "pl", "pt",
        "ro", "ru", "sr", "sk", "sl", "es", "sv", "th", "tr", "uk",
        "vi", "zh-CN", "zh-TW",
};

char* valid_times[] = {
        "h", "d", "w", "m", "y",
};

/*
 * Helper function to check if a string is in an array of strings.
 *
 * Returns 1 if string is found. 0 otherwise.
 */
static int str_is_in_array(char* str, char* str_array[], size_t array_len)
{
        for (unsigned i = 0; i < array_len; i++) {
                if (strcmp(str, str_array[i]) == 0) {
                        return 1;
                }
        }

        return 0;
}

static void set_lang(char* oarg)
{
        size_t len = sizeof(valid_langs) / sizeof(valid_langs[0]); 
        if (str_is_in_array(oarg, valid_langs, len)) {
                settings.lang = oarg;          
        } else {
                print_usage();
        }
}

static void set_country(char* oarg)
{
        size_t len = sizeof(valid_countries) / sizeof(valid_countries[0]); 
        if (str_is_in_array(oarg, valid_countries, len)) {
                settings.country = oarg;          
        } else {
                print_usage();
        }
}

static void set_time(char* oarg)
{
        size_t len = sizeof(valid_times) / sizeof(valid_times[0]); 
        if (str_is_in_array(oarg, valid_times, len)) {
                settings.time = oarg;          
        } else {
                print_usage();
        }
}

static void set_num_results(char* oarg)
{
        long val = strtol(oarg, NULL, 10);

        if (errno == EINVAL || errno == ERANGE || val <= 0)
        {
                print_usage();
        }

        settings.num_results = val;
}

static void set_start_result(char* oarg)
{
        long val = strtol(oarg, NULL, 10);

        if (errno == EINVAL || errno == ERANGE || val < 0)
        {
                print_usage();
        }

        settings.start_result = val;
}

static void set_search_string(char* oarg)
{
        settings.search_string = oarg;
}

static void set_display_mode(char* oarg)
{
        if (strcmp("list", oarg) == 0) {
                settings.display_mode = LIST_MODE;
        } else if (strcmp("table", oarg) == 0) {
                settings.display_mode = TABLE_MODE;
        } else {
                print_usage();
        }
}

static void parse_long_opts(const char* name, char* oarg)
{
        if (strcmp("searchintitle", name) == 0) {
                settings.search_in_title = 1;
        }
}

void parse_arguments(int argc, char* argv[])
{
        int option, long_index = 0;

        while ((option = getopt_long(argc, argv, optstring, 
                                    long_opts, &long_index)) >= 0) {
                switch (option) {
                        case 0:
                                parse_long_opts(long_opts[long_index].name,
                                                optarg);
                                break;
                        case 's':
                                set_search_string(optarg);
                                break;
                        case 'n':
                                set_num_results(optarg);
                                break;
                        case 'N':
                                set_start_result(optarg);
                                break;
                        case 'l':
                                set_lang(optarg);
                                break;
                        case 'c':
                                set_country(optarg);
                                break;
                        case 't':
                                set_time(optarg);
                                break;
                        case 'd':
                                set_display_mode(optarg);
                                break;
                        case '?':
                        case 'h':
                        default:
                                print_usage();
                                break;
                       }
        }
}

void print_usage()
{
        fprintf(stderr, "Invalid usage.\n");
        exit(EXIT_FAILURE);
}
