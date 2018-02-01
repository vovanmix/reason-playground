[@bs.module "react-select"]
external reactSelect : ReasonReact.reactClass = "default";

type reactSelectOption('a) = {
  .
  "value": 'a,
  "label": string
};

let hanldeChange = (record: reactSelectOption('a)) : 'a => record##value;

let make =
    (
      ~value: 'a,
      ~onChange: 'a => unit,
      ~options: array(reactSelectOption('a)),
      children
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=reactSelect,
    ~props={
      "value": value,
      "onChange": r => hanldeChange(r) |> onChange,
      "options": options
    },
    children
  );
