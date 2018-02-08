let component = ReasonReact.statelessComponent("IndexPage");

let make = _children => {
  ...component,
  render: _self =>
    <div> (ReasonReact.stringToElement("Hello I'm a dashboard")) </div>
};
