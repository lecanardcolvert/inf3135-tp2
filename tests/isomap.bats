examples_folder=../examples
prog=../bin/isomap
help_first_line="Usage: ../bin/isomap [-h|--help] [-s|--start X,Y,Z] [-e|--end X,Y,Z]"

# Normal usage

@test "Show help with short option -h" {
    run $prog -h
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Usage: ../bin/isomap [-h|--help] [-s|--start X,Y,Z] [-e|--end X,Y,Z]" ]
    [ "${lines[1]}" = "    [-w|--with-walk] [-f|--output-format FORMAT]" ]
    [ "${lines[2]}" = "    [-i|--input-filename PATH] [-o|--output-filename PATH]" ]
}

@test "Show help with long option --help" {
    run $prog --help
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "$help_first_line" ]
}

@test "Can read map3x3.json file from stdin" {
    run $prog < ../data/map3x3.json
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Tileset of 3 tiles:" ]
    [ "${lines[4]}" = "A map of 2 layers" ]
}

@test "Can read map3x3.json file with option -i" {
    run $prog -i ../data/map3x3.json
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Tileset of 3 tiles:" ]
    [ "${lines[4]}" = "A map of 2 layers" ]
}

@test "No walk in map3x3.json with default values for -s and -e" {
    run $prog -w < ../data/map3x3.json
    [ "$status" -eq 0 ]
    [[ "${lines[13]}" =~ "No walk between" ]]
}

@test "There is a walk of 5 nodes in map3x3.json with -s 0,0,1 and -e 2,2,1" {
    run $prog -w -s 0,0,1 -e 2,2,1 < ../data/map3x3.json
    [ "$status" -eq 0 ]
    [[ "${lines[13]}" =~ "A walk of 5 nodes" ]]
}

@test "Format \"text\" works with map3x3.json" {
    run $prog -f text < ../data/map3x3.json
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Tileset of 3 tiles:" ]
    [ "${lines[4]}" = "A map of 2 layers" ]
}

@test "Format \"png\" works with map3x3.json" {
    run $prog -f png -o "$BATS_TMPDIR"/map3x3.png < ../data/map3x3.json
    [ "$status" -eq 0 ]
    [ -f "$BATS_TMPDIR/map3x3.png" ]
}

# Errors

@test "Format \"dot\" not supported yet" {
    run $prog -f dot
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "Error: format dot not supported" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "Wrong coordinates with -s a,2,2" {
    run $prog -s a,2,2
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "Error: the coordinates must be 3 integers separated by commas" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "Wrong coordinates with -e 0,0" {
    run $prog -e 0,0
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "Error: the coordinates must be 3 integers separated by commas" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "Output file path mandatory with format \"png\"" {
    run $prog -f png
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "Error: output filename is mandatory with png format" ]
}

@test "Option -z is not recognized" {
    run $prog -z
    [ "$status" -eq 4 ]
    [ "${lines[1]}" = "Error: option not recognized" ]
}

@test "Handle invalid input file path" {
    run $prog -i "$BATS_TMPDIR/epic.fail"
    [ "$status" -eq 5 ]
    [ "${lines[0]}" = "Error: invalid file path" ]
}

@test "Handle invalid output file path" {
    run $prog -o "$BATS_TMPDIR/epic.fail/fail" < ../data/map3x3.json
    [ "$status" -eq 5 ]
    [ "${lines[0]}" = "Error: invalid file path" ]
}
