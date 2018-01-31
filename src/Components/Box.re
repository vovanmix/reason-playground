let component = ReasonReact.statelessComponent("Box");

let make = _children => {
  ...component,
  render: _self =>
    <div className="Box"> (ReasonReact.stringToElement("Box Content")) </div>
};
