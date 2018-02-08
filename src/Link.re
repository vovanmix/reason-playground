let component = ReasonReact.statelessComponent("Link");

let make = (~to_: Routing.route, ~active=false, ~className="", children) => {
  ...component,
  render: _self => {
    let url = Routing.reverseLink(to_);
    let className_ = active ? className ++ " active" : className;
    <a
      className=className_
      href=url
      onClick=(
        event => {
          ReactEventRe.Synthetic.preventDefault(event);
          ReasonReact.Router.push(url);
        }
      )>
      (ReasonReact.arrayToElement(children))
    </a>;
  }
};

module Link = {
  let make = make;
};

module Text = {
  let component = ReasonReact.statelessComponent("TextLink");
  let make = (~to_, ~text, ~active=false, ~className="", ~icon="", _children) => {
    ...component,
    render: _self =>
      <Link className to_ active>
        (
          icon != "" ?
            <i key="1" className=("fa fa-" ++ icon) /> : ReasonReact.nullElement
        )
        (ReasonReact.stringToElement(text))
      </Link>
  };
};

module Button = {
  let component = ReasonReact.statelessComponent("ButtonLink");
  let make = (~to_, ~text, ~color="info", ~icon="", _children) => {
    ...component,
    render: _self => <Text to_ text icon className=("btn btn-" ++ color) />
  };
};
