open Utils;

requireCSS("assets/styles/app.sass");

let logo = requireAssetURI("assets/images/logo.svg");

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <h2 className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <strong className="App-title">
          (ReasonReact.stringToElement(message))
        </strong>
      </h2>
      <p className="App-intro">
        (ReasonReact.stringToElement("We're working hard!!"))
      </p>
      <PersonCreate />
      <PersonList />
    </div>
};
