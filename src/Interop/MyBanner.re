[@bs.module "src/interop/MyBanner"]
external myBanner : ReasonReact.reactClass = "default";

let make = (~show, ~message, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=myBanner,
    ~props={
      "show": Js.Boolean.to_js_boolean(show), /* ^ don't forget to convert an OCaml bool into a JS boolean! */
      "message": message /* OCaml string maps to JS string, no conversion needed here */
    },
    children
  );
