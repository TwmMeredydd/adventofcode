let use_example_inputs = ref false;;

let specs = [
    ("-e", Arg.Set use_example_inputs, "Use example inputs");
];;
Arg.parse specs (fun s -> ()) "";;

let input_filename = if !use_example_inputs then "input.example.txt" else "../../inputs/2025/01.txt";;

let input_lines = String.split_on_char '\n' (In_channel.with_open_bin input_filename In_channel.input_all);;

let modulo x y = ((x mod y) + y) mod y;;

let partOne = 
    let rec count list dial = (
        match list with
        | [] -> 0
        | x :: v -> (
            let newDial = modulo (dial + (int_of_string (String.sub x 1 ((String.length x) - 1))) * (if x.[0] == 'L' then -1 else 1)) 100 in
            count v newDial + if newDial == 0 then 1 else 0
        )
    ) in
    count input_lines 50;;

print_endline (string_of_int (partOne));;

let partTwo = 
    let rec count list dial = (
        match list with
        | [] -> 0
        | x :: v -> (
            let rot = int_of_string (String.sub x 1 ((String.length x) - 1)) in
            let zeroDiff = if dial == 0 then 100 else if x.[0] == 'L' then dial else (100-dial) mod 100 in 
            let newDial = modulo (if x.[0] == 'L' then dial - rot else dial + rot) 100 in
            (if rot>=zeroDiff then (rot-zeroDiff) / 100 + 1 else 0) + count v newDial
        )
    ) in
    count input_lines 50;;

print_endline (string_of_int (partTwo));;