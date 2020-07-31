/**
 * main.c
 *
 * Generate isometric map from a command line
 *
 * @author Alexandre Blondin Masse
 */
#include "isomap.h"
#include "geometry.h"
#include "graph.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#define FORMAT_LENGTH 5
#define FILENAME_LENGTH 200
#define USAGE "\
Usage: %s [-h|--help] [-s|--start X,Y,Z] [-e|--end X,Y,Z]\n\
    [-w|--with-walk] [-f|--output-format FORMAT]\n\
    [-i|--input-filename PATH] [-o|--output-filename PATH]\n\
\n\
Generate an isometric map from a JSON file. The file must respect\n\
the right JSON format. See the README file for more details.\n\
By default, read the file on stdin and write the result on stdout.\n\
\n\
Optional arguments:\n\
  -h|--help                  Show this help message and exit.\n\
  -s|--start X,Y,Z           The start location (X,Y,Z) in the map.\n\
                             Default value is (0,0,0).\n\
  -e|--end X,Y,Z             The end location (X,Y,Z) in the map.\n\
                             Default value is (1,1,0).\n\
  -w|--with-walk             Also display a shortest walk between\n\
                             the start and end locations.\n\
  -f|--output-format FORMAT  Select the ouput format (either text,\n\
                             dot, or png). The default format is text.\n\
  -i|--input-filename PATH   Read the JSON file from the file PATH\n\
                             If present, ignore stdin.\n\
  -o|--output-filename PATH  Write the output to the file PATH.\n\
                             Mandatory for the PNG output format.\n\
                             If present, does not write on stdout.\n\
"

/**
 * Parsing errors
 */
enum status {
    ISOMAP_OK                                = 0,
    ISOMAP_ERROR_FORMAT_NOT_SUPPORTED        = 1,
    ISOMAP_ERROR_COORDINATES                 = 2,
    ISOMAP_ERROR_PNG_FORMAT_WITHOUT_FILENAME = 3,
    ISOMAP_ERROR_BAD_OPTION                  = 4,
    ISOMAP_ERROR_INVALID_PATH                = 5,
};

/**
 * Arguments from the command line
 */
struct arguments {
    bool show_help;                        // Show help?
    bool with_walk;                        // Display walk?
    struct location start;                 // The start location
    struct location end;                   // The end location
    char output_format[FORMAT_LENGTH];     // The output format
    char input_filename[FILENAME_LENGTH];  // The input filename
    char output_filename[FILENAME_LENGTH]; // The output filename
    enum status status;                    // The status of the program
};

// Functions //
// --------- //

/**
 * Retrieve the (x,y,z) coordinates from a string
 *
 * @param s  The string containing the coordinates
 * @param x  The given layer
 * @param y  The given row
 * @param z  The given column
 * @return   The status
 */
enum status parse_coordinates(const char *s, int *x, int *y, int *z) {
    char tail = '\0';
    int num_parsed = sscanf(s, "%d,%d,%d%c", x, y, z, &tail);
    return num_parsed == 3 && tail == '\0' ? ISOMAP_OK : ISOMAP_ERROR_COORDINATES;
}

/**
 * Print usage to a stream
 *
 * @param argv  The command line arguments
 * @param file  The stream
 */
void print_usage(char *argv[], FILE *file) {
    fprintf(file, USAGE, argv[0]);
}

/**
 * Parse the command line arguments
 *
 * @param argc  The number of arguments
 * @param argv  The arguments
 * @return      The parsed arguments
 */
struct arguments parse_arguments(int argc, char *argv[]) {
    struct arguments arguments = {
        .show_help       = false,
        .with_walk       = false,
        .output_format   = "text",
        .input_filename  = "",
        .output_filename = "",
        .status          = ISOMAP_OK
    };
    arguments.start.x = 0;
    arguments.start.y = 0;
    arguments.start.z = 0;
    arguments.end.x   = 1;
    arguments.end.y   = 1;
    arguments.end.z   = 0;
    struct option long_opts[] = {
        // Set flag
        {"help",            no_argument,       0, 'h'},
        {"with-walk",       no_argument,       0, 'w'},
        // Don't set flag
        {"start",           required_argument, 0, 's'},
        {"end",             required_argument, 0, 'e'},
        {"output-format",   required_argument, 0, 'f'},
        {"input-filename",  required_argument, 0, 'i'},
        {"output-filename", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    while (true) {
        int option_index = 0;
        int c = getopt_long(argc, argv, "hws:e:f:i:o:", long_opts, &option_index);
        if (c == -1) break;
        switch (c) {
            case 'h': arguments.show_help = true; break;
            case 'w': arguments.with_walk = true; break;
            case 's': arguments.status = arguments.status != ISOMAP_OK ? arguments.status :
                                         parse_coordinates(optarg, &arguments.start.x,
                                                           &arguments.start.y, &arguments.start.z);
                      break;
            case 'e': arguments.status = arguments.status != ISOMAP_OK ? arguments.status :
                                         parse_coordinates(optarg, &arguments.end.x,
                                                           &arguments.end.y, &arguments.end.z);
                      break;
            case 'f': strncpy(arguments.output_format, optarg, FORMAT_LENGTH - 1);
                      break;
            case 'i': strncpy(arguments.input_filename, optarg, FILENAME_LENGTH - 1);
                      break;
            case 'o': strncpy(arguments.output_filename, optarg, FILENAME_LENGTH - 1);
                      break;
            case '?': arguments.status = ISOMAP_ERROR_BAD_OPTION;
                      break;
        }
    }

    if (arguments.status == ISOMAP_ERROR_BAD_OPTION || optind < argc) {
        fprintf(stderr, "Error: option not recognized\n");
        print_usage(argv, stderr);
        exit(ISOMAP_ERROR_BAD_OPTION);
    } else if (arguments.show_help) {
        print_usage(argv, stdout);
        exit(ISOMAP_OK);
    } else if (arguments.status == ISOMAP_ERROR_COORDINATES) {
        fprintf(stderr, "Error: the coordinates must be 3 integers separated by commas\n");
        print_usage(argv, stderr);
        exit(ISOMAP_ERROR_COORDINATES);
    } else if (strcmp(arguments.output_format, "text") != 0 &&
               strcmp(arguments.output_format, "dot") != 0 && 
               strcmp(arguments.output_format, "png")  != 0) {
        fprintf(stderr, "Error: format %s not supported\n", arguments.output_format);
        print_usage(argv, stderr);
        exit(ISOMAP_ERROR_FORMAT_NOT_SUPPORTED);
    } else if (strcmp(arguments.output_format, "png") == 0 &&
               strcmp(arguments.output_filename, "")  == 0) {
        fprintf(stderr, "Error: output filename is mandatory with png format\n");
        print_usage(argv, stderr);
        exit(ISOMAP_ERROR_PNG_FORMAT_WITHOUT_FILENAME);
    }
    return arguments;
}

/**
 * Print a walk in the isomap to stdout, if it exists
 *
 * @param isomap     The isomap
 * @param arguments  The parsed arguments
 */
void print_walk(const struct isomap *isomap,
                const struct arguments *arguments) {
    struct graph *graph = graph_create(isomap->map, isomap->tileset);
    struct graph_walk *walk = graph_shortest_walk(graph,
            &arguments->start,
            &arguments->end);
    if (walk != NULL) {
        printf("A ");
        graph_print_walk(stdout, walk, "");
    } else {
        printf("No walk between ");
        geometry_print_location(stdout, &arguments->start);
        printf(" and ");
        geometry_print_location(stdout, &arguments->end);
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    struct arguments arguments = parse_arguments(argc, argv);
    if (arguments.status == ISOMAP_OK) {
        FILE *input = stdin;
        if (strcmp(arguments.input_filename, "") != 0) {
            input = fopen(arguments.input_filename, "r");
            if (input == NULL) {
                fprintf(stderr, "Error: invalid file path\n");
                exit(ISOMAP_ERROR_INVALID_PATH);
            }
        }
        struct isomap *isomap = isomap_create_from_json_file(input);
        if (input != stdin)
            fclose(input);
        FILE *output = stdout;
        if (strcmp(arguments.output_filename, "") != 0) {
            output = fopen(arguments.output_filename, "w");
            if (output == NULL) {
                fprintf(stderr, "Error: invalid file path\n");
                exit(ISOMAP_ERROR_INVALID_PATH);
            }
        }
        if (strcmp(arguments.output_format, "text") == 0) {
            isomap_print(output, isomap, "");
            if (arguments.with_walk) print_walk(isomap, &arguments);
            if (output != stdout) fclose(output);
        } else if (strcmp(arguments.output_format, "dot") == 0) {
            struct graph *graph = graph_create(isomap->map, isomap->tileset);
            if (arguments.with_walk) graph_print_to_dot_walk(output, graph,
                                                            &arguments.start,
                                                            &arguments.end);
            if (!arguments.with_walk) graph_print_to_dot(output, graph);
            graph_delete(graph);
        } else if (strcmp(arguments.output_format, "png") == 0) {
            isomap_draw_to_png(isomap, arguments.output_filename);
        }
        isomap_delete(isomap);
    }
    return arguments.status;
}
