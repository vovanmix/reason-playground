open PersonTypes;

type state = person;

type action =
  | UpdateName(string)
  | UpdateCountry(int)
  | UpdateEnabled(bool)
  | UpdateAddresses(list(address))
  | UpdateFile(option(string))
  | Submit;

let component = ReasonReact.reducerComponent("PersonForm");

let countries: array(ReactSelect.reactSelectOption(int)) = [|
  {"value": 1, "label": "opt one"},
  {"value": 2, "label": "opt two"},
  {"value": 2, "label": "opt three"}
|];

let make = (~onSubmit, ~saving=false, ~initialState: person, _children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | UpdateName(name) => ReasonReact.Update({...state, name})
    | UpdateCountry(country) => ReasonReact.Update({...state, country})
    | UpdateEnabled(enabled) => ReasonReact.Update({...state, enabled})
    | UpdateAddresses(addresses) => ReasonReact.Update({...state, addresses})
    | UpdateFile(file) => ReasonReact.Update({...state, file})
    | Submit => ReasonReact.UpdateWithSideEffects(state, ((_) => onSubmit(state)))
    },
  render: self =>
    <div className="Box">
      <h2> (ReasonReact.stringToElement("Create new stuff")) </h2>
      <div> (ReasonReact.stringToElement(saving ? "saving" : "not saving")) </div>
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
      <fieldset className="form-group">
        <ImageSelector
          value=self.state.file
          onChange=(value => self.send(UpdateFile(value)))
        />
      </fieldset>
      <fieldset className="form-group">
        <FormList
          items=self.state.addresses
          label="Addresses"
          onChange=(value => self.send(UpdateAddresses(value)))
          defaultValue={street: "", zip: 0}
          renderItem=((item, onChange) => <Address address=item onChange />)
        />
      </fieldset>
      <button
        disabled=(Js.Boolean.to_js_boolean(saving))
        onClick=(_event => self.send(Submit))>
        (ReasonReact.stringToElement("Submit"))
      </button>
    </div>
};
