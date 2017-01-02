#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include "settings.h"
#include "options.h"

static char* optstring = "s:n:N:l:c:t:d:";

static struct option long_opts[] = {
        {"search", required_argument, NULL, 's'},
        {"num", required_argument, NULL, 'n'},
        {"startnum", required_argument, NULL, 'N'},
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

char* valid_languages[] = {
        "ar", "hy", "be", "bg", "ca", "hr", "cs", "da", "nl", "en",
        "eo", "et", "tl", "fi", "fr", "de", "el", "iw", "hu", "is",
        "id", "it", "ja", "ko", "lv", "lt", "no", "fa", "pl", "pt",
        "ro", "ru", "sr", "sk", "sl", "es", "sv", "th", "tr", "uk",
        "vi", "zh-CN", "zh-TW",
}

/*
 * Helper function to check if a string is in an array of strings.
 *
 * Returns 1 if string is found. 0 otherwise.
 */
static int is_str_in_array(char* str, char* str_array[], int array_len)
{
        for (int i = 0; i < array_len; i++) {
                if (strcmp(str, str_array[i]) == 0) {
                        return 1;
                }
        }

        return 0;
}

static void set_num_results(char* oarg)
{
        long val = strtol(oarg);

        if (errno == EINVAL || errno == ERANGE)
        {
                print_usage();
        }

        settings.num_results = val;
}

static void set_start_num(char* oarg)
{
        long val = strtol(oarg);

        if (errno == EINVAL || errno == ERANGE)
        {
                print_usage();
        }

        settings.start_num = val;
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
}

void parse_arguments(int argc, char* argv[])
{
        int option, long_index = 0;

        while((option = getopt_long(argc, argv, optstring, 
                                    long_opts, &long_index)) >= 0)
        {
                switch (option) {
                        case 's':
                                set_search_string(optarg);
                                break;
                        case 'n':
                                set_num_result(optarg);
                                break;
                        case 'N':
                                set_start_num(optarg);
                                break;
                        case 'l':
                                break;
                        case 'c':
                                break;
                        case 't':
                                break;
                        case 'd':
                                set_display_mode(optarg);
                                break;
                        case '0':
                                parse_long_opts(long_opts[long_index].name,
                                                optarg);
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
        fprintf(stderr, "Invalid usage.");
        exit(EXIT_FAILURE);

}
