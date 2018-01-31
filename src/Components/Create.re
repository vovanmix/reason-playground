type state = {
  country: int,
  name: string,
  enabled: bool,
  addresses: list(Types.address)
};

type action =
  | UpdateName(string)
  | UpdateCountry(int)
  | UpdateEnabled(bool)
  | UpdateAddresses(list(Types.address))
  | Submit;

let component = ReasonReact.reducerComponent("Create");

let countries: array(ReactSelect.reactSelectOption(int)) = [|
  {"value": 1, "label": "opt one"},
  {"value": 2, "label": "opt two"},
  {"value": 2, "label": "opt three"}
|];

let initialState = {
  country: 0,
  name: "",
  enabled: false,
  addresses: [{street: "Elm st", zip: 10342}]
};

let callSubmit = form : unit => {
  Js.log("submit!");
  Js.log(form);
};

let make = (~saving=false, _children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | UpdateName(name) => ReasonReact.Update({...state, name})
    | UpdateCountry(country) => ReasonReact.Update({...state, country})
    | UpdateEnabled(enabled) => ReasonReact.Update({...state, enabled})
    | UpdateAddresses(addresses) => ReasonReact.Update({...state, addresses})
    | Submit => ReasonReact.UpdateWithSideEffects(state, ((_) => callSubmit(state)))
    },
  render: self =>
    <div className="Box">
      <h2> (ReasonReact.stringToElement("Create new stuff")) </h2>
      <div> (ReasonReact.stringToElement(saving ? "saving" : "not saving")) </div>
      <MyBanner show=true message="hi there" />
      <fieldset className="form-group">
        <ReactSelect
          value=self.state.country
          onChange=(value => self.send(UpdateCountry(value)))
          options=countries
        />
      </fieldset>
      <fieldset className="form-group">
        <Text
          value=self.state.name
          onChange=(value => self.send(UpdateName(value)))
          placeholder="Name"
        />
      </fieldset>
      <fieldset className="form-group">
        <Checkbox
          value=self.state.enabled
          onChange=(value => self.send(UpdateEnabled(value)))
        />
      </fieldset>
      <Addresses
        addresses=self.state.addresses
        onChange=(value => self.send(UpdateAddresses(value)))
      />
      <button
        disabled=(Js.Boolean.to_js_boolean(saving))
        onClick=(_event => self.send(Submit))>
        (ReasonReact.stringToElement("Submit"))
      </button>
    </div>
};
