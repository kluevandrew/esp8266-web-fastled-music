import { TemplatesList } from "./templates/templates.list";

export class Renderer {

  private templateContextFunctions = {
    include: (template, context) => {
      try {
        return this.compileTemplate(TemplatesList[template], context)
      } catch (e) {
        return `<pre>${e.message}\n${e.stack.split('\n').map(function (line) { return line.trim(); })}</pre>`;
      }
    },
    keyToId: (key: string) => {
      return key.split('.').join('_');
    },
    compile: this.compileTemplate.bind(this),
  };

  private static escapeHTML(string) {
    string = `${string}`;
    return string.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  }

  private compileTemplate(template: string, context: any = {}) {
    return template
      .replace(/#if\s*?\((.+?)\)((.|\n)*)#endif/igm, (match: string, ifClause: string, inner: string) => {
        return this.evalTemplateCode(ifClause.trim(), context) ? inner : '';
      })
      .replace(/#foreach\s*\((.+?)\s*?as\s*(.+?)(\s*,\s*(.*?))?\)((.|\n)*)#endforeach/igm, (match: string, arrayCode: string, itemName: string, _: string, keyName: string, inner: string, b) => {
        const iterator = this.evalTemplateCode(arrayCode.trim(), context);
        let value = '';
        for (let key in iterator) {
          if (!iterator.hasOwnProperty(key)) {
            continue;
          }
          context[itemName.trim()] = iterator[key];
          if (keyName) {
            context[keyName.trim()] = key;
          }
          value += this.compileTemplate(inner, context);
        }

        context[itemName] = undefined;
        if (keyName) {
          context[keyName.trim()] = undefined;
        }
        return value;
      })
      .replace(/\{\%\s*?(.+?)\s*?\%\}/ig, (match: string, code: string) => {
        return this.evalTemplateCode(code.trim(), context);
      })
      .replace(/\{\{\s*?(.+?)\s*?\}\}/ig, (match: string, key: string) => {
        return Renderer.escapeHTML(this.evalTemplateCode(`context.${key}`, context));
      });
  }

  private evalTemplateCode(js, context) {
    //# Return the results of the in-line anonymous function we .call with the passed context
    return function () {
      return eval(`var engine = this.engine; var context = this.context; ${js}`);
    }.call({
      engine: this.templateContextFunctions,
      context: context,
    });
  }

  public render(name: string, context: any = {}): HTMLElement {
    const html = this.compileTemplate(TemplatesList[name], context);

    const div = document.createElement('div');
    div.innerHTML = html;
    return div;
  }
}
