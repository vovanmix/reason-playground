[@bs.module "react-simple-file-reader-input"]
external reactFileReaderInput : ReasonReact.reactClass = "default";

type file = {
  type_: string,
  name: string,
  size: int
};

type jsFile = {
  .
  "type": string,
  "name": string,
  "size": int
};

type res = {. "result": string};

type event = {. "target": res};

type oneFile = (event, jsFile);

type results = Js.Array.t(oneFile);

type fileResult = {
  file,
  result: string
};

let getData = (_, results: results) : array(fileResult) =>
  results
  |> Js.Array.map(f => {
       let (event, jsFile) = f;
       let file = {
         type_: [%bs.raw {| jsFile.type |}],
         name: jsFile##name,
         size: jsFile##size
       };
       {result: event##target##result, file};
     });

let make =
    (
      ~accept: string,
      ~as_: string,
      ~onChange: array(fileResult) => unit,
      ~className: string,
      children
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=reactFileReaderInput,
    ~props={
      "id": "dsfds",
      "accept": accept,
      "as": as_,
      "className": className,
      "onChange": (a, b) => getData(a, b) |> onChange
    },
    children
  );
