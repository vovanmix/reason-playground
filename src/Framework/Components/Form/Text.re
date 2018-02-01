let component = ReasonReact.statelessComponent("Text");

let make = (~value, ~onChange, ~placeholder="", _children) => {
  let hanldeChange = event => FormUtils.valueFromEvent(event) |> onChange;
  {
    ...component,
    render: _self =>
      <input
        _type="text"
        className="form-control"
        placeholder
        value
        onChange=hanldeChange
      />
  };
};
