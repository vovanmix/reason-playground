type qs = list((string, string));

type sectionPath = {
  action: option(string),
  id: option(int),
  qs
};

let encodeQueryString = qs =>
  qs
  |> List.fold_left(
       (acc, tuple) => {
         let (l, r) = tuple;
         acc ++ "&" ++ l ++ "=" ++ r;
       },
       ""
     );

let makeUrlTail = path =>
  switch path {
  | {action: None, id: Some(id), qs} => string_of_int(id) ++ encodeQueryString(qs)
  | {action: Some(act), id: None, qs} => act ++ encodeQueryString(qs)
  | {action: Some(act), id: Some(id), qs} =>
    act ++ "/" ++ string_of_int(id) ++ encodeQueryString(qs)
  | _ => encodeQueryString(path.qs)
  };

let makeSectionPath = (prefix, section, path) =>
  prefix ++ section ++ "/" ++ makeUrlTail(path);

let parseQueryString = (qs: string) =>
  qs
  |> Js.String.split("&")
  |> Array.to_list
  |> List.map(s => s |> Js.String.split("=") |> Array.to_list)
  |> List.filter(s => List.length(s) == 2)
  |> List.map(s =>
       switch s {
       | [f, l] => (f, l)
       | _ => ("", "")
       }
     );

let isInt = str =>
  switch (int_of_string(str)) {
  | i when i > 0 => true
  | _ => false
  | exception _ => false
  };

let parseSectionUrl = (rem, search) => {
  let qs = parseQueryString(search);
  switch rem {
  | [id] when isInt(id) => {action: None, id: Some(int_of_string(id)), qs}
  | [id, action] when isInt(id) => {
      action: Some(action),
      id: Some(int_of_string(id)),
      qs
    }
  | [action] => {action: Some(action), id: None, qs}
  | _ => {action: None, id: None, qs}
  };
};
