open RoutingUtils;

let prefix = "/";

type section =
  | People;

type route =
  | Index
  | Login
  | Section(section, sectionPath)
  | NotFound(list(string));

let reverseLink = route =>
  switch route {
  | Section(People, path) => makeSectionPath(prefix, "people", path)
  | _ => prefix
  };

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch url.path {
  | ["people", ...rem] => Section(People, parseSectionUrl(rem, url.search))
  | [] => Index
  | path => NotFound(path)
  };

/*
 #################
 ###### LIB ######
 #################
 */
let redirect = route => route |> reverseLink |> ReasonReact.Router.push;

let redirectSection = (route, path) => Section(route, path) |> redirect;

let reverseLinkSection = (route, path) => Section(route, path) |> reverseLink;

let mkSectionRoute = (section, ~action=?, ~id=None, ~qs=[], ()) =>
  Section(section, {action, id, qs});

let sectionPathEqual = (pathA, pathB) =>
  switch (pathA, pathB) {
  | ({action: Some(a), id: Some(idA)}, {action: Some(b), id: Some(idB)}) =>
    a == b && idA == idB
  | ({action: Some(a)}, {action: Some(b)}) => a == b
  | ({action: None, id: None}, {action: None, id: None}) => true
  | _ => false
  };
