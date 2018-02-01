let component = ReasonReact.statelessComponent("Checkbox");

let make = (~value, ~onChange, ~placeholder="", _children) => {
  let hanldeChange = event => FormUtils.checkedFromEvent(event) |> onChange;
  {
    ...component,
    render: _self =>
      <input
        _type="checkbox"
        title=placeholder
        checked=(Js.Boolean.to_js_boolean(value))
        onChange=hanldeChange
      />
  };
};
