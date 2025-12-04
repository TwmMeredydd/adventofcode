let use_example_inputs = ref false
let specs = [ ("-e", Arg.Set use_example_inputs, "Use example inputs") ];;

Arg.parse specs (fun s -> ()) "";;

let input_filename =
  if !use_example_inputs then "input.example.txt"
  else "../../inputs/2025/02.txt"

let input_list =
  let strings =
    String.split_on_char ','
      (In_channel.with_open_bin input_filename In_channel.input_all)
  in
  List.map
    (fun s -> List.map (fun t -> int_of_string t) (String.split_on_char '-' s))
    strings

(* print_endline (String.concat " " (List.map (fun l -> String.concat "-" (List.map (fun x -> string_of_int x) l)) input_list)) *)

let partOne =
  let rec countInvalidsInRange low high =
    if low > high then 0
    else
      let s = string_of_int low in
      let invalid =
        if String.length s mod 2 == 1 then 0
        else if
          String.sub s 0 (String.length s / 2)
          = String.sub s (String.length s / 2) (String.length s / 2)
        then low
        else 0
      in
      invalid + countInvalidsInRange (low + 1) high
  in
  let rec countInvalids list =
    match list with
    | [] -> 0
    | head :: tail ->
        countInvalidsInRange (List.nth head 0) (List.nth head 1)
        + countInvalids tail
  in
  countInvalids input_list
;;

print_endline @@ string_of_int partOne;;

let partTwo =
  let rec checkRepeats pattern word =
    let patternLength = String.length pattern in
    if word = "" then pattern <> ""
    else if patternLength = 0 || patternLength > String.length word then false
    else if patternLength <> 0 && pattern = String.sub word 0 patternLength then
      checkRepeats pattern
        (String.sub word patternLength (String.length word - patternLength))
    else false
  in
  let rec splitWord head tail =
    if checkRepeats head tail then true
    else if String.length tail = 1 then false
    else
      splitWord
        (head ^ String.sub tail 0 1)
        (String.sub tail 1 (String.length tail - 1))
  in
  let rec countInvalidsInRange low high =
    if low > high then 0
    else
      (if splitWord "" (string_of_int low) then low else 0)
      + countInvalidsInRange (low + 1) high
  in
  let rec countInvalids list =
    match list with
    | [] -> 0
    | head :: tail ->
        countInvalidsInRange (List.nth head 0) (List.nth head 1)
        + countInvalids tail
  in
  countInvalids input_list
;;

print_endline @@ string_of_int partTwo
