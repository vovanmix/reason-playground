let valueFromEvent = evt : string => (
                                       evt
                                       |> ReactEventRe.Form.target
                                       |> ReactDOMRe.domElementToObj
                                     )##value;

let checkedFromEvent = evt : bool =>
  Js.to_bool(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(evt))##checked);
