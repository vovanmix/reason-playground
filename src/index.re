open JsUtils;

requireCSS("assets/styles/app.sass");

ReactDOMRe.renderToElementWithId(<App />, "root");

ReasonReact.Router.push([%bs.raw {| window.location.pathname |}]);

if (hot) {
  accept();
};
